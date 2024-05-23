#include "Tile.hpp"
#include <vector>

namespace views {
    /********************************************************************
     * The Dashboard is the home page of the app.
     * It displays a tile for each game, separated by game categories
     ********************************************************************/
    class Dashboard {

        std::vector<ui_elements::Tile> _category1Tiles;
        std::vector<ui_elements::Tile> _category2Tiles;

    public:
        void addTileToCategory1(const ui_elements::Tile &tile);

        void addTileToCategory2(const ui_elements::Tile &tile);

        static void renderCategory(const std::string &categoryName, const std::vector<ui_elements::Tile> &tiles);

        void render() const;
    };
}
