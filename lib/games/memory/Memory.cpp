//
// Created by Admin on 15.06.2024.
//

#include <thread>
#include "Memory.hpp"
#include "GameSessionManager.hpp"
#include "InfoBox.hpp"
#include "Window.hpp"
#include "Centered.hpp"

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

        loadImages();
    }

    void Memory::loadImages() {
        _imagePaths = {
                "1.png",

        };
    }

    void Memory::initializeTiles() {
        for (int i = 0; i < 30; ++i) {
            int imageIndex = i % 15; // Ensure pairs of images
            auto tile = std::make_shared<memory::MemoryTile>(_imagePaths[imageIndex], [this, i]() { handleTileClick(i); }, _tileSize);
            _tiles.push_back(tile);
        }
    }

    void Memory::arrangeTiles() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(_tiles.begin(), _tiles.end(), g);

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
    }

    void Memory::handleTileClick(int tileID) {
        // Handle tile click logic
        // This is where you check for matches and manage the game state
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

        _timer = std::make_unique<ui_elements::Timer>(_gameName, 10);
        _timer->start();

        resetTiles();
        for (auto& tile : _tiles) {
            tile->flip();
        }

        std::thread([this] {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            flipTilesBack();
        }).detach();

    }

    void Memory::stop() {
        _showEndBox = true;
        _isGameRunning = false;
    }

    void Memory::reset() {
        _tiles.clear();
        _coordinates.clear();
        _timer.reset();
    }

    void Memory::updateStatistics() {
        // ignore for now
    }

    std::string Memory::getName() const {
        return _gameName;
    }


}