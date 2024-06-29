#ifndef ATHENA_MEMORY_HPP
#define ATHENA_MEMORY_HPP

#include "Game.hpp"
#include "Colors.hpp"
#include "Timer.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "RandomPicker.hpp"
#include "MemoryTile.hpp"
#include "MemoryGameImageManager.hpp"
#include <imgui.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>

namespace memory {

    class Memory : public abstract_game::Game {
        ImVec4 _windowColor{commons::ColorTheme::BACKGROUND_COLOR};
        std::unique_ptr<ui_elements::Timer> _timer;
        std::vector<std::shared_ptr<MemoryTile>> _tiles;
        std::vector<Coordinates> _coordinates;
        MemoryGameImageManager& _imageManager; // Use MemoryGameImageManager for managing images

        bool _showAllTiles{false}; //unused

        ImVec2 _tileSize{140, 140};
        float _padding{15.0f};

        std::shared_ptr<MemoryTile> _firstTile{nullptr};
        std::shared_ptr<MemoryTile> _secondTile{nullptr};
        int _pairsFound{0};
        bool _isCheckingMatch{false};
        int _totalGameTime{30};

        std::chrono::steady_clock::time_point _matchCheckTime;
        bool _delayActive{false};

        void initializeTiles();
        void arrangeTiles();
        void handleTileClick(int tileID);
        void resetTiles();
        void flipTilesBack();
        void centerTiles();

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