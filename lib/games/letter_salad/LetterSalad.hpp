//
// Created by Benjamin Puhani on 08.06.2024.
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_

#include "Game.hpp"
#include "Coordinates.hpp"

using Box = std::pair<std::string, bool>;

namespace game {

using CharVector2D = std::vector<std::vector<Box>>;

class LetterSalad : Game {
  // initialize game field with 20x20 "x"
  CharVector2D _gameField{20, {20, {"X", false}}};
  // save clicked cells
  Coordinates _firstSelectedCell{-1, -1};
  Coordinates _secondSelectedCell{-1, -1};
  bool _isFirstCellSelected{false};
  bool _isSecondCellSelected{false};
  void update();
  void clickCell(Coordinates coords);
  void pairSelected();
  void resetSelectedPair();
  static std::vector<Coordinates> getLine(Coordinates &start, Coordinates &end);
  void selectBox(Coordinates &coords);
  void deSelectBox(Coordinates &coords);
 public:
  void stop() override;
  std::string getName() const override;
  void render() override;
  void renderGame() override;
  void start() override;
  void reset() override;
  void updateStatistics() override;

};

}
#endif //ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
