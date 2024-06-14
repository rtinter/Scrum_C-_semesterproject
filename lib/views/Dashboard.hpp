#include "Tile.hpp"
#include <vector>
#include <map>
#include <memory>

using String = std::string;
using UniqueTile = std::unique_ptr<ui_elements::Tile>;

namespace views {

/**************************************************************
 * The _dashboard holds a vector of categories with which the
 * user can start games by clicking on them.
 **************************************************************/
class Dashboard {
  std::map<String, std::vector<UniqueTile>> _categoryTiles;
  void addTileToCategory(String const &category, UniqueTile &tile);
 public:
  void addTilesToCategory(String const &category,
                          std::vector<UniqueTile> &tiles
  );
  void render();
};
}
