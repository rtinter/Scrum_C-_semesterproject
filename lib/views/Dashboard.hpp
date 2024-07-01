#pragma once

#include <memory>
#include <vector>

#include "Tile.hpp"

using String = std::string;
using UniqueTile = std::unique_ptr<ui_elements::Tile>;

namespace views {
    /**
     * The _dashboard holds a vector of categories with which the
     * user can start games by clicking on them.
     */
    class Dashboard {
        std::unordered_map<String, std::vector<UniqueTile> > _categoryTiles;

        void addTileToCategory(String const &category, UniqueTile &tile);

    public:
        void addTilesToCategory(String const &category,
                                std::vector<UniqueTile> &tiles
        );

        void render();
    };
} // views
