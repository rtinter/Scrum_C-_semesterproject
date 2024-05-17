#include "Tile.h"
#include <vector>

namespace views {
    class Dashboard {

        std::vector<ui_elements::Tile> _category1Tiles;
        std::vector<ui_elements::Tile> _category2Tiles;

    public:
        void addTileToCategory1(const ui_elements::Tile& tile);
        void addTileToCategory2(const ui_elements::Tile& tile);
        void render();
    };
}
