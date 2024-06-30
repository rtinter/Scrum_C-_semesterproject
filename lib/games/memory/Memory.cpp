#include "Memory.hpp"
#include "GameSessionManager.hpp"
#include "InfoBox.hpp"
#include "Window.hpp"
#include "Centered.hpp"
#include "SoundPolice.hpp"

namespace memory {

    Memory::Memory() : abstract_game::Game(abstract_game::GameID::MEMORY),
                       _imageManager(MemoryGameImageManager::getInstance()) {
        _gameName = "Memory";
        _gameDescription =
                "Memory ist ein Spiel, welches deine Konzentration und Merkfähigkeit auf die Probe stellt.\n"
                "Schauen wir mal, ob du auch unter Druck einen kühlen Kopf bewahren kannst.\n"
                "Zwei gleiche Bilder bilden ein Paar, Kannst du sie alle vor Ablauf der Zeit finden?\n"
                "Viel Glück und viel Vergnügen!\n";

        _gameRules =
                "1. Du darfst alle Bildpaare einmal ansehen, anschließend werden sie gemischt und verdeckt umgedreht.\n"
                "2. Pro Zug kannst du immer nur zwei Karten aufdecken.\n"
                "3. Zeigen beide Karten das gleiche Bild, hast du ein Paar und die Karten bleiben aufgedeckt.\n"
                "4. Passen die Karten nicht zusammen, werden sie wieder umgedreht und du verlierst eine Sekunde.\n"
                "5. Du musst alle Paare in 120 Sekunden finden und möglichst wenige Züge dafür benötigen.\n";

        _gameControls =
                "Steuerung:\n"
                "1. Du benötigst nur die linke Maustaste, um zu Klicken.\n"
                "2. Tippe nacheinander die beiden Karten deiner Wahl an, um sie aufzudecken.\n"
                "3. Klicke entweder sofort weiter oder warte 2 Sekunden, bis die Karten sich zudecken.\n"
                "4. Klicke auf 'Versuch es nochmal', um das Spiel zurückzusetzen und es erneut zu versuchen.\n"
                "5. Klicke auf 'Zurück zur Startseite', um zum Hauptmenü zurückzukehren.";

    }

    void Memory::initializeTiles() {
        _tiles.clear(); // Clear existing tiles

        // Generate indices for the images
        std::vector<int> indices(30);
        for (int i{0}; i < 30; ++i) {
            indices[i] = i % 15; // Create pairs of indices (0 to 14)
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g); // Shuffle the image indices

        for (int i{0}; i < 30; ++i) {
            int imageIndex = indices[i];
            sf::Texture &texture {_imageManager.getTexture(imageIndex)};
            auto tile = std::make_shared<memory::MemoryTile>(texture, [this, i]() { handleTileClick(i); }, _tileSize,
                                                             imageIndex);
            _tiles.push_back(tile);
        }
    }


    void Memory::arrangeTiles() {

        int const columns{10};
        int const rows[]{1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

        _coordinates.clear(); // Ensure coordinates are cleared before arranging

        int index{0};
        for (int col{0}; col < columns; ++col) {
            for (int row{0}; row < rows[col]; ++row) {
                _coordinates.emplace_back(row * (_tileSize.y + _padding), col * (_tileSize.x + _padding));
                ++index;
            }
        }

    }


    void Memory::centerCoordinates() {
        int const columns{10};
        int const rows[]{1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

        float const totalWidth{columns * (_tileSize.x + _padding) - _padding};
        float const totalHeight{5 * (_tileSize.y + _padding) - _padding};

        ImVec2 windowSize{ImGui::GetWindowSize()};
        float startX{(windowSize.x - totalWidth) / 2};
        float startY{(windowSize.y - totalHeight) / 2};

        int index{0};
        for (int col{0}; col < columns; ++col) {
            int yOffset{static_cast<int>(startY + (5 - rows[col]) * (_tileSize.y + _padding) /
                                                  2)}; // Center each column vertically
            for (int row{0}; row < rows[col]; ++row) {
                float x{startX + col * (_tileSize.x + _padding)};
                float y{yOffset + row * (_tileSize.y + _padding)};
                if (index < _tiles.size()) {
                    _coordinates[index] = Coordinates(y, x);
                    ++index;
                }
            }
        }
    }

    void Memory::showAllTiles() {
        for (auto &tile: _tiles) {
            if (!tile->isFaceUp()) {
                tile->flip();
            }
        }
    }

    void Memory::hideAllTiles() {
        for (auto &tile: _tiles) {
            if (tile->isFaceUp()) {
                tile->flip();
            }
        }
    }

    void Memory::startGameTimer() {
        _timer = std::make_unique<ui_elements::Timer>(_gameName, _totalGameTime);
        _timer->start();
    }

    void Memory::handleTileClick(int tileID) {
        if (!_initialDisplayDone || _isCheckingMatch) {
            handleMismatch(); // Immediately handle mismatch if a new tile is clicked
        }

        auto &tile{_tiles[tileID]};

        if (tile->isFaceUp()) {
            return; // Ignore if the tile is already flipped
        }

        // Play sound when a tile is flipped open
        commons::SoundPolice::safePlaySound(commons::Sound::CARD_FLIP, 60, 2.5f);

        tile->flip();

        if (!_firstTile) {
            _firstTile = tile;
        } else if (!_secondTile) {
            _secondTile = tile;
            _isCheckingMatch = true;
            checkForMatch();
        }
    }


    void Memory::checkForMatch() {
        if (_firstTile->getIndex() == _secondTile->getIndex()) {
            commons::SoundPolice::safePlaySound(commons::Sound::CORRECT, 60, 1.5f);
            _pairsFound++;
            _firstTile = nullptr;
            _secondTile = nullptr;
            _isCheckingMatch = false;
            if (_pairsFound == 15) {
                checkForWin(); // Check for win immediately when all pairs are found
            }
        } else {
            _matchCheckTime = std::chrono::steady_clock::now();
            _delayActive = true;
        }
    }

    void Memory::handleMismatch() {
        if (_isCheckingMatch) {
            _timer->reduceTime(1);
            resetFlippedTiles();
            _firstTile = nullptr;
            _secondTile = nullptr;
            _isCheckingMatch = false;
            _delayActive = false;
        }
    }

    void Memory::checkForWin() {
        // Calculate time taken
        int timeTaken{_totalGameTime - _timer->getSecondsLeft()};
        int minutes{timeTaken / 60};
        int seconds{timeTaken % 60};

        // Format time as <minutes:seconds>
        _timeTakenString = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

        // Update end box message
        _endBoxTitle = "Gut gemacht!";
        _endBoxText = "Du hast " + std::to_string(_pairsFound) + " Paare gefunden.\n"
                                                                 "Dafür hast du " + _timeTakenString +
                      " Minuten gebraucht.";

        stop();
    }


    void Memory::handleGameOver() {
        // Calculate time taken
        int timeTaken{_totalGameTime - _timer->getSecondsLeft()};
        int minutes{timeTaken / 60};
        int seconds{timeTaken % 60};

        // Format time as <minutes:seconds>
        _timeTakenString = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

        // Update end box message
        std::string pairString{_pairsFound == 1 ? "Paar" : "Paare"};
        _endBoxTitle = "Spiel vorbei!";
        _endBoxText = "Zeit abgelaufen.\n"
                      "Du hast " + std::to_string(_pairsFound) + " " + pairString + " gefunden.";

        stop();
    }

    void Memory::resetFlippedTiles() {
        if (_firstTile && _secondTile) {
            _firstTile->flip();
            _secondTile->flip();
        }
    }


    void Memory::render() {
        ui_elements::InfoBox(
                _gameID,
                _showStartBox,
                "Startbox",
                _gameName,
                _gameDescription,
                _gameRules,
                _gameControls,
                [this] {
                    start();
                }).render();

        ui_elements::InfoBox(
                _gameID,
                _showEndBox,
                "Endbox",
                _endBoxTitle,
                _endBoxText,
                [this] {
                    reset();
                    start();
                }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    void Memory::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);
        ui_elements::Window("Memory").render([this] {

            _timer->render();

            auto now{std::chrono::steady_clock::now()};
            if (std::chrono::duration_cast<std::chrono::seconds>(now - _initialDisplayStartTime).count() < 3) {
                if (!_initialDisplayDone) {
                    initializeTiles();
                    arrangeTiles();
                    centerCoordinates();
                    showAllTiles();
                    _initialDisplayDone = true;
                }
                _timer->reset();
            } else {
                if (_timerPaused) {
                    hideAllTiles();
                    initializeTiles();
                    arrangeTiles();
                    centerCoordinates();
                    startGameTimer();
                    _timerPaused = false;
                }
            }


            if (_timer && _timer->isExpiredNow()) {
                handleGameOver();
            }


            if (_delayActive) {
                auto nowDelay{std::chrono::steady_clock::now()};
                if (std::chrono::duration_cast<std::chrono::seconds>(nowDelay - _matchCheckTime).count() >= 2) {
                    handleMismatch();
                }
            }


            for (int i {0}; i < _tiles.size(); ++i) {
                auto &tile {_tiles[i]};
                auto coords {_coordinates[i]};
                ImGui::SetCursorPos(ImVec2(coords.x, coords.y));
                tile->render();
            }


        });
        ImGui::PopStyleColor();
    }

    void Memory::start() {
        _isGameRunning = true;
        _showStartBox = false;
        _showEndBox = false;
        _initialDisplayDone = false;

        startGameTimer();
        _initialDisplayStartTime = std::chrono::steady_clock::now();
    }

    void Memory::stop() {
        _showEndBox = true;
        _isGameRunning = false;
    }

    void Memory::reset() {
        _tiles.clear();
        _coordinates.clear();
        _timer.reset();
        _firstTile = nullptr;
        _secondTile = nullptr;
        _pairsFound = 0;
        _initialDisplayDone = false;
        _timerPaused = true;
    }

    void Memory::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("benötigte Zeit",
                                                                                     _totalGameTime - _timer->getSecondsLeft());
    }

    std::string Memory::getName() const {
        return _gameName;
    }
}