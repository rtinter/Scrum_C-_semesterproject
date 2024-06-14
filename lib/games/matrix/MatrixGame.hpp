#ifndef ATHENA_MATRIX_HPP
#define ATHENA_MATRIX_H

#include "Game.hpp"
#include "Colors.hpp"
#include "Timer.hpp"
#include "Matrix.hpp"

namespace games {

    class MatrixGame : public abstract_game::Game {
        ui_elements::Timer _timer{"Matrix Game", 10};
        int _nCorrectClicksInTotal;
        int _longestStreak;
        int _nColoredCellsMin;
        int _nColoredCellsMax;
        Matrix _mainMatrix;
        std::array<Matrix, 2> _allMirroredVersions;
        std::array<Matrix, 3> _allRotatedVersions;
        std::array<Matrix, 3> _matricesToChooseFrom;
        bool _isClicked;

        void checkForCorrectClick();

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
