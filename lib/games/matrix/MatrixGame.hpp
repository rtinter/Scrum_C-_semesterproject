#ifndef ATHENA_MATRIX_HPP

#include "Game.hpp"
#include "Colors.hpp"
#include "Timer.hpp"
#include "Matrix.hpp"

namespace game {

    class MatrixGame : public abstract_game::Game {
        ui_elements::Timer _timer{"Matrix Game", 120};
        int _nCorrectClicksInTotal;
        int _longestStreak;
        int _nCellsWithNumbersMin;
        int _nCellsWithNumbersMax;
        int _nCellsWithNumbers;
        int _nCorrectClicksSinceLastError;
        int _idOfCorrectMatrix;
        Matrix _mainMatrix;
        enum class GameMode {
            MIRROR,
            ROTATE
        };
        GameMode _currentGameMode;
        std::array<Matrix, 3> _matricesToChooseFrom;

        void renderAnswerOptions();

        void renderQuestion();

        void renderQuestionText();

        void generateNewMatrices();

        void initMatricesToChooseFrom();

        void onClick(bool isCorrect);


    public:
        MatrixGame();

        void stop() override;

        void render() override;

        void renderGame() override;

        void start() override;

        void reset() override;

        void updateStatistics() override;

    };

} // game

#endif //ATHENA_MATRIX_HPP
