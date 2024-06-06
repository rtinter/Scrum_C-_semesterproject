#include "Tile.hpp"
#include <vector>
#include <map>

namespace views {

    /**************************************************************
     * The dashboard holds a vector of categories with which the
     * user can start games by clicking on them.
     **************************************************************/
    class Dashboard {
        std::map<std::string, std::vector<ui_elements::Tile>> _categoryTiles;
        void addTileToCategory(const std::string &category, const ui_elements::Tile &tile);
    public:
        void addTilesToCategory(const std::string &category, const std::vector<ui_elements::Tile> &tiles);
        void render();
    };
}
