#pragma once

#define EMPTY_CELL "_" // empty cell
#define NR_OF_WORDS 15 // number of words to be searched
#define TIME_LIMIT (15 * 60) // time limit for the game

#include <set>

#include "Box.hpp"
#include "Coordinates.hpp"
#include "Game.hpp"
#include "RandomPicker.hpp"
#include "Timer.hpp"
#include "WordTarget.hpp"

namespace games {
    using RandomPicker = commons::RandomPicker;
    using CharVector2D = std::vector<std::vector<letter_salad::Box> >;

    /**
     * @brief The LetterSalad game class, which represents the logic and rendering of the game.
     */
    class LetterSalad final : abstract_game::Game {
        CharVector2D _gameField;
        std::vector<commons::Coordinates> _currentLine;
        static std::vector<letter_salad::WordTarget> _wordList;
        ui_elements::Timer _timer{"####letterSalad", TIME_LIMIT};
        std::set<letter_salad::WordTarget> _activeWordList;
        // save clicked cells
        commons::Coordinates _firstSelectedCell{-1, -1};
        bool _isFirstCellSelected{false};
        bool _isSecondCellSelected{false};
        std::string _selectedWord;
        double _wordsPerMinute;

        static void loadWordsFromFile();

        void clickCell(commons::Coordinates const &coords);

        void resetSelectedPair();

        static std::vector<commons::Coordinates> getLine(commons::Coordinates const &start,
                                                         commons::Coordinates const &end);

        void onHover(commons::Coordinates const &coords);

        void selectBox(commons::Coordinates const &coords);

        void deselectBox(commons::Coordinates const &coords);

        void finalize(commons::Coordinates const &coords);

        void randomizeGameField();

        void renderTextList() const;

        void timerExpired();

        void allWordsFound();

        bool isWordInList(std::set<letter_salad::WordTarget> &wordlist, std::string const &word);

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
} // games
