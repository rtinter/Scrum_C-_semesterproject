//
// Created by Benjamin Puhani (941077) on 08.06.2024.
// &22 Buchstabensalat
//

#ifndef ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
#define ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_

#define EMPTY_CELL "_" // empty cell
#define NR_OF_WORDS 15 // number of words to be searched
#define TIME_LIMIT (15 * 60) // time limit for the game

#include "Game.hpp"
#include "Coordinates.hpp"
#include "Box.hpp"
#include "WordTarget.hpp"
#include "Timer.hpp"
#include <set>
#include "RandomPicker.hpp"

namespace game {

    using RandomPicker = commons::RandomPicker;
    using CharVector2D = std::vector<std::vector<Box>>;

    class LetterSalad : abstract_game::Game {
      CharVector2D _gameField;
      std::vector<Coordinates> _currentLine;
      static std::vector<WordTarget> _wordList;
      ui_elements::Timer _timer{"####letterSalad", TIME_LIMIT};
      std::set<WordTarget> _activeWordList;
      // save clicked cells
      Coordinates _firstSelectedCell{-1, -1};
      bool _isFirstCellSelected{false};
      bool _isSecondCellSelected{false};
      std::string _selectedWord;
      static void loadWordsFromFile();
      void clickCell(Coordinates const &coords);
      void resetSelectedPair();
      static std::vector<Coordinates> getLine(Coordinates const &start, Coordinates const &end);
      void onHover(Coordinates const &coords);
      void selectBox(Coordinates const &coords);
      void deselectBox(Coordinates const &coords);
      void finalize(Coordinates const &coords);
      void randomizeGameField();
      void renderTextList();
      bool isWordInList(std::set<WordTarget> &wordlist, std::string const &word);
      void renderGameField();
      void renderSelectedWord() const;
      void fillGameFieldWithRandomWords();
      bool placeWord(std::string word);
     public:
      LetterSalad();
      void stop() override;
      std::string getName() const override;
      void render() override;
      void renderGame() override;
      void start() override;
      void reset() override;
      void updateStatistics() override;
      void init();
    };

}
#endif //ATHENA_LIB_GAMES_LETTER_SALAD_LETTERSALAD_HPP_
