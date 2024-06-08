//
// Created by benni on 08.06.2024.
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_

#include "Game.hpp"
namespace game {

using CharVector2D = std::vector<std::vector<std::pair<std::string, bool>>>;

class LetterSalad : Game {
  // initialize game field with 20x20 "x"
  CharVector2D _gameField{20, {20, {"X", false}}};
  void update();
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
