//
// Created by Benjamin Puhani on 08.06.2024.
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_

#include "Game.hpp"
#include "Coordinates.hpp"
#include "Box.hpp"

namespace game {

using WordTarget = std::pair<std::string, bool>;
using CharVector2D = std::vector<std::vector<Box>>;

class LetterSalad : Game {
  static CharVector2D _gameField;
  static std::vector<Coordinates> _currentLine;
  static std::vector<WordTarget> _wordList;
  // save clicked cells
  Coordinates _firstSelectedCell{-1, -1};
  Coordinates _secondSelectedCell{-1, -1};
  bool _isFirstCellSelected{false};
  bool _isSecondCellSelected{false};
  std::string _selectedWord;
  void update();
  void clickCell(Coordinates const &coords);
  void pairSelected();
  void resetSelectedPair();
  static std::vector<Coordinates> getLine(Coordinates const &start, Coordinates
  const &end);
  void onHover(const Coordinates &coords);
  static void selectBox(Coordinates const &coords);
  static void deSelectBox(Coordinates const &coords);
  static void randomizeGameField();
  void renderGameField();
  void renderSelectedWord() const;
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
