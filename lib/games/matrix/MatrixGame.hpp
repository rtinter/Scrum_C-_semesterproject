#pragma once

#include "Game.hpp"
#include "Matrix.hpp"
#include "Timer.hpp"

namespace games {
    /**
     * @brief: provides logic and visuals for the game 'Matrix'
     */
    class MatrixGame final : public abstract_game::Game {
        ui_elements::Timer _timer{"Matrix Game", 120};
        int _nCorrectClicksInTotal;
        int _longestStreak;
        int _nMarkedCellsMin;
        int _nMarkedCellsMax;
        int _nMarkedCells;
        int _nCorrectClicksSinceLastError;
        int _idOfCorrectMatrix;
        matrix::Matrix _mainMatrix;

        enum class GameMode {
            MIRROR,
            ROTATE
        };

        GameMode _currentGameMode;
        std::array<matrix::Matrix, 3> _matricesToChooseFrom;

        void renderAnswerOptions();

        void renderQuestion() const;

        void renderQuestionText() const;

        void generateNewMatrices();

        void initMatricesToChooseFrom();

        void onClick(bool const &isCorrect);

    public:
        MatrixGame();

        void stop() override;

        void render() override;

        void renderGame() override;

        void start() override;

        void reset() override;

        void updateStatistics() override;
    };
} // games
