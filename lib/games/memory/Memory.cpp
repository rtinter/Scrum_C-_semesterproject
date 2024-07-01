#include "Memory.hpp"

#include <random>

#include "GameSessionManager.hpp"
#include "InfoBox.hpp"
#include "SoundPolice.hpp"
#include "Window.hpp"
#include "WindowConfig.hpp"

namespace games {
    Memory::Memory() : Game(abstract_game::GameID::MEMORY),
                       _imageManager(memory::MemoryGameImageManager::getInstance()) {
        _gameName = "Memory";
        _gameDescription =
                "Memory ist ein Spiel, welches deine Konzentration und Merkfähigkeit auf die Probe stellt.\n"
                "Schauen wir mal, ob du auch unter Druck einen kühlen Kopf bewahren kannst.\n"
                "Zwei gleiche Bilder bilden ein Paar, kannst du sie alle vor Ablauf der Zeit finden?\n"
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
        _tiles.clear();

        // Create pairs of indices for the images
        std::vector<int> indices(30);
        for (int i{0}; i < 30; ++i) {
            indices[i] = i % 15;
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g); // Shuffle the image indices

        for (int i{0}; i < 30; ++i) {
            int const imageIndex{indices[i]};

            // Retrieve the texture corresponding to the image index from the image manager
            sf::Texture const &texture{_imageManager.getTexture(imageIndex)};

            // Create a new memory tile with the retrieved texture, a click handler, tile size, and image index
            auto const tile{
                std::make_shared<memory::MemoryTile>(texture, [this, i] { handleTileClick(i); }, _tileSize,
                                                     imageIndex)
            };

            _tiles.push_back(tile);
        }
    }


    void Memory::arrangeTiles() {
        constexpr int COLUMNS{10};
        constexpr int ROWS[]{1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

        _coordinates.clear();

        // Assign coordinates to each tile
        int index{0};
        for (int col{0}; col < COLUMNS; ++col) {
            for (int row{0}; row < ROWS[col]; ++row) {
                _coordinates.emplace_back(row * (_tileSize.y + _tilePadding), col * (_tileSize.x + _tilePadding));
                ++index;
            }
        }
    }


    void Memory::centerCoordinates() {
        constexpr int COLUMNS{10};
        constexpr int ROWS[]{1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

        // Calculate total width and height of the tile formation
        float const totalWidth{((_tileSize.x + _tilePadding) * COLUMNS) - _tilePadding};
        float const totalHeight{(5 * (_tileSize.y + _tilePadding)) - _tilePadding};

        // Calculate the start position for the tile formation
        float const startX{(commons::WindowConfig::WINDOW_WIDTH - totalWidth) / 2};
        float const startY{(commons::WindowConfig::WINDOW_HEIGHT - totalHeight) / 2};

        int index{0};

        for (int col{0}; col < COLUMNS; ++col) {
            int const yOffset{
                static_cast<int>(startY + ((5 - ROWS[col]) * (_tileSize.y + _tilePadding) /
                                 2))
            };
            for (int row{0}; row < ROWS[col]; ++row) {
                float const x{startX + (col * (_tileSize.x + _tilePadding))};
                float const y{yOffset + (row * (_tileSize.y + _tilePadding))};
                // Assign the calculated coordinates to the tile if within bounds
                if (index < _tiles.size()) {
                    _coordinates[index] = commons::Coordinates(y, x);
                    ++index;
                }
            }
        }
    }

    void Memory::showAllTiles() {
        for (auto const &tile: _tiles) {
            if (!tile->isFaceUp()) {
                tile->flip();
            }
        }
    }

    void Memory::hideAllTiles() {
        for (auto const &tile: _tiles) {
            if (tile->isFaceUp()) {
                tile->flip();
            }
        }
    }

    void Memory::startGameTimer() {
        _timer = std::make_unique<ui_elements::Timer>(_gameName, _totalGameTime);
        _timer->start();
    }

    void Memory::handleTileClick(int const tileID) {
        if (_isCheckingMatch) {
            handleMismatch();
        }

        auto const &tile{_tiles[tileID]};

        if (tile->isFaceUp()) {
            return;
        }

        tile->flip();

        commons::SoundPolice::safePlaySound(Sound::CARD_FLIP, 60, 2.5f);

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
            commons::SoundPolice::safePlaySound(Sound::CORRECT, 60, 1.5f);
            _pairsFound++;
            _firstTile = nullptr;
            _secondTile = nullptr;
            _isCheckingMatch = false;
            if (_pairsFound == 15) {
                checkForWin();
            }
        }
        // If the two tiles do not match, delay for 2 seconds before flipping them back
        else {
            _matchCheckTime = std::chrono::steady_clock::now();
            _delayActive = true;
        }
    }

    void Memory::handleMismatch() {
        if (_isCheckingMatch) {
            _timer->reduceTime(1); // Reduce time by 1 second for mismatch
            resetMismatchedTiles();
            _firstTile = nullptr;
            _secondTile = nullptr;
            _isCheckingMatch = false;
            _delayActive = false;
        }
    }

    void Memory::checkForWin() {
        int const timeTaken{_totalGameTime - _timer->getSecondsLeft()};
        int const minutes{timeTaken / 60};
        int const seconds{timeTaken % 60};

        _timeTakenString = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

        _endBoxTitle = "Gut gemacht!";
        _endBoxText = "Du hast " + std::to_string(_pairsFound) + " Paare gefunden.\n"
                      "Dafür hast du " + _timeTakenString +
                      " Minuten gebraucht.";

        stop();
    }


    void Memory::handleGameOver() {
        int const timeTaken{_totalGameTime - _timer->getSecondsLeft()};
        int const minutes{timeTaken / 60};
        int const seconds{timeTaken % 60};

        _timeTakenString = std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);

        std::string const pairString{_pairsFound == 1 ? "Paar" : "Paare"};
        _endBoxTitle = "Spiel vorbei!";
        _endBoxText = "Zeit abgelaufen.\n"
                      "Du hast " + std::to_string(_pairsFound) + " " + pairString + " gefunden.";

        stop();
    }

    void Memory::resetMismatchedTiles() const {
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

            if (auto const now{std::chrono::steady_clock::now()}; std::chrono::duration_cast<std::chrono::seconds>(now - _initialDisplayStartTime).count() < 3) {
                // Prepare tiles once for the initial display
                if (!_initialDisplayDone) {
                    initializeTiles();
                    arrangeTiles();
                    centerCoordinates();
                    showAllTiles();
                    _initialDisplayDone = true;
                }
                // Reset timer to prevent time from running during initial display (equivalent to pause)
                _timer->reset();
            } else {
                // Handle tiles once after the initial display is done
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
                if (auto const nowDelay{std::chrono::steady_clock::now()}; std::chrono::duration_cast<std::chrono::seconds>(nowDelay - _matchCheckTime).count() >= 2) {
                    // If 2 seconds have passed, handle the mismatch
                    handleMismatch();
                }
            }

            // Render each tile at its assigned coordinates
            for (int i{0}; i < _tiles.size(); ++i) {
                auto const &tile{_tiles[i]};
                auto const coords{_coordinates[i]};
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

        // Capture the current time to track the start of the initial display
        _initialDisplayStartTime = std::chrono::steady_clock::now();
    }

    void Memory::stop() {
        _showEndBox = true;
        _isGameRunning = false;
        updateStatistics();
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
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("Sekunden benötigt",
            _totalGameTime -
            _timer->getSecondsLeft());
    }

    std::string Memory::getName() const {
        return _gameName;
    }
} // games
