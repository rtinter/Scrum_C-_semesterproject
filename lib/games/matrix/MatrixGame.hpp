#ifndef ATHENA_MATRIX_HPP
#define ATHENA_MATRIX_H

#include "Game.hpp"
#include "Colors.hpp"
#include "Timer.hpp"
#include "Matrix.hpp"

namespace games {

    class MatrixGame : public abstract_game::Game {
        ui_elements::Timer _timer{"Matrix Game", 60};
        std::string _endboxString;
        int _numberOfCorrectClicksInTotal;
        int _longestStreak;
        Matrix _mainMatrix;

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

#endif //ATHENA_MATRIX_HPP
