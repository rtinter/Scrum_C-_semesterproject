#include "Tile.h"
#include <vector>

class Dashboard {



    std::vector<ui_elements::Tile> category1Tiles;
    std::vector<ui_elements::Tile> category2Tiles;

public:
    void addTileToCategory1(const ui_elements::Tile& tile);
    void addTileToCategory2(const ui_elements::Tile& tile);
    void render();
};


