#pragma once

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

namespace games {
    /**
     * @brief Memory game class. Represents the logic and rendering of the Memory game.
     */
    class Memory final : public abstract_game::Game {
        ImVec4 _windowColor{commons::ColorTheme::BACKGROUND_COLOR};

        std::unique_ptr<ui_elements::Timer> _timer;
        int _totalGameTime{150};

        std::vector<std::shared_ptr<memory::MemoryTile> > _tiles;
        std::shared_ptr<memory::MemoryTile> _firstTile{nullptr};
        std::shared_ptr<memory::MemoryTile> _secondTile{nullptr};

        ImVec2 _tileSize{140, 140};
        float _tilePadding{15.0f};

        std::vector<commons::Coordinates> _coordinates;
        memory::MemoryGameImageManager &_imageManager;

        int _pairsFound{0};
        bool _isCheckingMatch{false};
        std::string _timeTakenString;

        std::chrono::steady_clock::time_point _matchCheckTime;
        std::chrono::steady_clock::time_point _initialDisplayStartTime;
        bool _initialDisplayDone{false};
        bool _delayActive{false};
        bool _timerPaused{true};

        /**
         * @brief Initializes the tiles for the game.
         */
        void initializeTiles();

        /**
         * @brief Arranges the tiles in a cool formation
         */
        void arrangeTiles();

        /**
         * @brief Centers the coordinates of the tiles to the window
         */
        void centerCoordinates();

        /**
         * @brief Shows the front of all tiles
         */
        void showAllTiles();

        /**
         * @brief Shows the back of all tiles
         */
        void hideAllTiles();

        /**
         * @brief Starts the game timer
         */
        void startGameTimer();

        /**
         * @brief Pauses the game timer
         *
         * @param tileID unique id for every tile
         */
        void handleTileClick(int tileID);

        /**
         * @brief Checks if the two flipped tiles match
         */
        void checkForMatch();

        /**
         * @brief Puts two mismatched tiles face-down
         */
        void resetMismatchedTiles() const;

        /**
         * @brief Handles results and EndBox text in winning case
         */
        void checkForWin();

        /**
         * @brief Handles results and EndBox text when not all pairs are found during game time
         */
        void handleGameOver();

        /**
         * @brief Handles the case when two tiles do not match
         */
        void handleMismatch();

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
} // games
