//
// Created by Admin on 15.06.2024.
//

#ifndef ATHENA_MEMORY_HPP
#define ATHENA_MEMORY_HPP

#include "Game.hpp"
#include "Colors.hpp"
#include "Timer.hpp"
#include "Tile.hpp"
#include "Coordinates.hpp"
#include "RandomPicker.hpp"
#include <imgui.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include "MemoryTile.hpp"

namespace memory {

    class Memory : public abstract_game::Game {
        ImVec4 _windowColor{commons::Colors::CORNFLOWER_BLUE};
        std::unique_ptr<ui_elements::Timer> _timer;
        std::vector<std::shared_ptr<MemoryTile>> _tiles;
        std::vector<Coordinates> _coordinates;
        std::vector<std::string> _imagePaths;

        bool _showAllTiles{false};

        ImVec2 _tileSize{140, 140};
        float _padding{15.0f};

        void initializeTiles();
        void loadImages();
        void arrangeTiles();
        void handleTileClick(int tileID);
        void resetTiles();
        void flipTilesBack();
        void centerTiles();

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
