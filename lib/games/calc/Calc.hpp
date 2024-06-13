#ifndef ATHENA_CALC_H
#define ATHENA_CALC_H

#include <string>
#include "Game.hpp"
#include "MathTask.hpp"
#include "MathTaskFactory.hpp"

namespace games {
    class Calc : public Game {
    public:
        Calc();
        void render() override;
        void start() override;

    private:
        int _completedLevels{0};
        std::unique_ptr<MathTask> _currentLevel;
        bool _showEndScreen{false};
        const char* _endScreenTitle{"Game Over"};
        const char* _endScreenText;

        void nextLevel();
        void showEndScreen();
    };
}

#endif // ATHENA_CALC_H
