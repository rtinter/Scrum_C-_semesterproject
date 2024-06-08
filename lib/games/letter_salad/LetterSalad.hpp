//
// Created by benni on 08.06.2024.
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
#include "Game.hpp"
namespace game {

class LetterSalad : Game {

  void stop() override;

 public:
  std::string getName() const override;
  void render() override;
  void renderGame() override;
  void start() override;
  void reset() override;
  void updateStatistics() override;
  ~LetterSalad() override = default;

};

}
#endif //ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
