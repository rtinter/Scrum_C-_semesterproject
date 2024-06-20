#include "Memory.hpp"
#include "GameSessionManager.hpp"
#include "InfoBox.hpp"
#include "Window.hpp"
#include "Centered.hpp"
#include <iostream>
#include <thread>

namespace memory {

    Memory::Memory() : abstract_game::Game(abstract_game::GameID::MEMORY) {
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
                "4. Passen die Karten nicht zusammen, werden sie wieder umgedreht und du verlierst 10 Sekunden.\n"
                "5. Du musst alle Paare in 120 Sekunden finden und möglichst wenige Züge dafür benötigen.\n";

        _gameControls =
                "Steuerung:\n"
                "1. Tippe nacheinander die beiden Karten deiner Wahl an, um sie aufzudecken.\n"
                "2. Klicke auf 'Versuch es nochmal', um das Spiel zurückzusetzen und es erneut zu versuchen.\n"
                "3. Klicke auf 'Zurück zur Startseite', um zum Hauptmenü zurückzukehren.";

        // Load images using ImageManager
        _imageManager = ImageManager();
    }

    void Memory::initializeTiles() {
        _tiles.clear(); // Clear existing tiles

        // Generate indices for the images
        std::vector<int> indices(30);
        for (int i = 0; i < 30; ++i) {
            indices[i] = i % 15; // Create pairs of indices (0 to 14)
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g); // Shuffle the image indices

        for (int i = 0; i < 30; ++i) {
            int imageIndex = i % 15; // Ensure pairs of images
            sf::Texture& texture = _imageManager.getTexture(imageIndex);
            auto tile = std::make_shared<memory::MemoryTile>(texture, [this, i]() { handleTileClick(i); }, _tileSize, imageIndex);
            _tiles.push_back(tile);
        }
    }


    void Memory::arrangeTiles() {
        std::random_device rd;
        std::mt19937 g(rd());

        const int columns = 10;
        const int rows[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

        _coordinates.clear(); // Ensure coordinates are cleared before arranging

        int index = 0;
        for (int col = 0; col < columns; ++col) {
            for (int row = 0; row < rows[col]; ++row) {
                _coordinates.emplace_back(row * (_tileSize.y + _padding), col * (_tileSize.x + _padding));
                ++index;
            }
        }

        std::shuffle(_coordinates.begin(), _coordinates.end(), g);
    }

    void Memory::handleTileClick(int tileID) {
        if (_isCheckingMatch) {
            return; // Ignore clicks while checking for a match
        }

        auto& tile = _tiles[tileID];

        if (tile->isFlipped()) {
            return; // Ignore if the tile is already flipped
        }

        tile->flip();

        if (!_firstTile) {
            _firstTile = tile;
        } else if (!_secondTile) {
            _secondTile = tile;
            _isCheckingMatch = true;
            checkForMatch();
        }
    }

    void Memory::resetTiles() {
        for (auto& tile : _tiles) {
            tile->reset();
        }
    }

    void Memory::flipTilesBack() {
        for (auto& tile : _tiles) {
            if (tile->isFlipped()) {
                tile->flip();
            }
        }
    }

    void Memory::centerTiles() {
        const int columns = 10;
        const int rows[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};

        const float totalWidth = columns * (_tileSize.x + _padding) - _padding;
        const float totalHeight = 5 * (_tileSize.y + _padding) - _padding;

        ImVec2 windowSize = ImGui::GetWindowSize();
        float startX = (windowSize.x - totalWidth) / 2;
        float startY = (windowSize.y - totalHeight) / 2;

        int index = 0;
        for (int col = 0; col < columns; ++col) {
            int yOffset = startY + (5 - rows[col]) * (_tileSize.y + _padding) / 2; // Center each column vertically
            for (int row = 0; row < rows[col]; ++row) {
                float x = startX + col * (_tileSize.x + _padding);
                float y = yOffset + row * (_tileSize.y + _padding);
                if (index < _tiles.size()) {
                    _coordinates[index] = Coordinates(y, x);
                    ++index;
                }
            }
        }
    }

    void Memory::checkForMatch() {
        std::thread([this] {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            if (_firstTile->getIndex() == _secondTile->getIndex()) {
                _pairsFound++;
            } else {
                _timer->reduceTime(10);
                resetFlippedTiles();
            }
            _firstTile = nullptr;
            _secondTile = nullptr;
            _isCheckingMatch = false;

            if (_pairsFound == 15) {
                stop();
            }
        }).detach();
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
            if (_tiles.empty()) {
                initializeTiles();
                arrangeTiles();
                centerTiles();
            }

            _timer->render();
            if (_timer->isExpiredNow()) {
                stop();
            }

            for (int i = 0; i < _tiles.size(); ++i) {
                auto& tile = _tiles[i];
                auto coords = _coordinates[i];
                ImGui::SetCursorPos(ImVec2(coords.x, coords.y));
                tile->render();
            }

            _endBoxTitle = "Spiel vorbei";
            _endBoxText = "Du hast int Paare gefunden!";
        });
        ImGui::PopStyleColor();
    }

    void Memory::start() {
        _isGameRunning = true;
        _showStartBox = false;
        _showEndBox = false;

        _timer = std::make_unique<ui_elements::Timer>(_gameName, 30);
        _timer->start();

        resetTiles();
        for (auto& tile : _tiles) {
            tile->flip();
        }


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
    }

    void Memory::updateStatistics() {
        // ignore for now
    }

    std::string Memory::getName() const {
        return _gameName;
    }
}