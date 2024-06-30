#ifndef ATHENA_MEMORY_HPP
#define ATHENA_MEMORY_HPP

#include <chrono>
#include <imgui.h>
#include <memory>
#include <vector>

#include "Coordinates.hpp"
#include "Game.hpp"
#include "MemoryGameImageManager.hpp"
#include "MemoryTile.hpp"
#include "Tile.hpp"
#include "Timer.hpp"

namespace memory {

    class Memory : public abstract_game::Game {
        ImVec4 _windowColor{commons::ColorTheme::BACKGROUND_COLOR};
        std::unique_ptr<ui_elements::Timer> _timer;
        std::vector<std::shared_ptr<MemoryTile>> _tiles;
        std::vector<commons::Coordinates> _coordinates;
        MemoryGameImageManager& _imageManager; // Use MemoryGameImageManager for managing images

        bool _initialDisplayDone{false};
        ImVec2 _tileSize{140, 140};
        float _padding{15.0f};

        std::shared_ptr<MemoryTile> _firstTile{nullptr};
        std::shared_ptr<MemoryTile> _secondTile{nullptr};
        int _pairsFound{0};
        bool _isCheckingMatch{false};
        int _totalGameTime{150};
        std::string _timeTakenString;

        std::chrono::steady_clock::time_point _matchCheckTime;
        std::chrono::steady_clock::time_point _initialDisplayStartTime;
        bool _delayActive{false};
        bool _timerPaused{true};

        void initializeTiles();
        void arrangeTiles();
        void centerCoordinates();
        void showAllTiles();
        void hideAllTiles();
        void startGameTimer();
        void handleTileClick(int tileID);
        void checkForMatch();
        void resetFlippedTiles();
        void checkForWin();
        void handleMismatch();
        void handleGameOver();

    public:
        explicit Memory();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override;

    };

} // memory

#endif //ATHENA_MEMORY_HPP
