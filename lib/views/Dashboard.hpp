#include "Tile.hpp"
#include <vector>
#include <map>

namespace views {
    class Dashboard {

        // std::vector<ui_elements::Tile> _category1Tiles;
        // std::vector<ui_elements::Tile> _category2Tiles;
        std::map<std::string, std::vector<ui_elements::Tile>> _categoryTiles;

    public:
        // void addTileToCategory1(const ui_elements::Tile& tile);
        // void addTileToCategory2(const ui_elements::Tile& tile);
        void addTileToCategory(const std::string& category, const ui_elements::Tile& tile);
        void addTilesToCategory(const std::string& category, const std::vector<ui_elements::Tile>& tiles);
        // void renderCategory(const std::string& categoryName, const std::vector<ui_elements::Tile>& tiles);
        void render();
    };
}
