#pragma once

#define NR_OF_SHOWN_SYMBOLS 6 // number of shown symbols in the row
#define TOTAL_TIME_SEC 90 // time limit for the game
#define SYMBOL_TIME_SEC 1.5f // time between symbol changes
#define WRONG_ANSWER_TIME_REDUCTION_SEC 5 // time reduction for wrong answer in seconds
#define NUMBER_OF_RECENTLY_USED_SYMBOLS 3 // number of recently used symbols that will not be shown next

#include <list>
#include <deque>
#include "Game.hpp"
#include "imgui.h"
#include "SymbolType.hpp"
#include "Timer.hpp"

namespace game {

    class RowsOfSymbols : abstract_game::Game {

        // list of currently shown symbols
        std::deque<SymbolType> _symbols;

        // number of correct symbols clicked
        int _correctSymbols {0};

        // number of wrong symbols clicked
        int _wrongSymbols {0};

        // list of recently used symbols
        std::deque<SymbolType> _lastAddedSymbols;

        // timer for the game to end the run-through after a certain time
        ui_elements::Timer _timer {"Symbolreihen", TOTAL_TIME_SEC};

        // time of the last symbol change, to skip the current symbol if the user is too slow to decide
        std::chrono::steady_clock::time_point _lastSymbolChange;

        /**
         * @brief Updates the list of shown symbols to have exactly NR_OF_SHOWN_SYMBOLS symbols
         */
        void updateShownSymbols();

        /**
         * @brief Renders a row of symbols
         */
        void renderRow();

        /**
         * @brief Renders the background rectangle for the row of symbols
         */
        static void renderBackgroundRect();

        /**
         * @brief Renders the two buttons for the user to click
         */
        void renderButtons();

        /**
         * @brief Gets called when the user clicks on the first button (0)
         */
        void clickButton0();

        /**
         * @brief Gets called when the user clicks on the second button (1)
         */
        void clickButton1();

        /**
         * @brief Pops the current symbol from the list of shown symbols
         */
        void popCurrentSymbol();

        /**
         * @brief Evaluates the answer of the user
         * @param correct whether the user pressed the correct button
         */
        void evaluateAnswer(bool correct);

        /**
         * @brief Checks whether the time for the current symbol is up
         * @return true if the time is up, false otherwise
         */
        bool isTimeUpForCurrentSymbol() const;

    public:
        RowsOfSymbols();
        std::string getName() const override;

        void render() override;
        void renderGame() override;

        void start() override;
        void reset() override;
        void stop() override;

        void updateStatistics() override;

    };
}