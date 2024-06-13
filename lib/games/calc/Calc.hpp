#ifndef ATHENA_CALC_H
#define ATHENA_CALC_H

#include <string>
#include "Game.hpp"
#include "MathTask.hpp"
#include "MathTaskFactory.hpp"

namespace games {
    class Calc : public abstract_game::Game {
    public:
        Calc();
        void render() override;

        void renderGame() override;
        void reset() override;
        void start() override;
        void stop() override;
        void updateStatistics() override;
        std::string getName() const override;

    private:
        int _completedLevels{0};
        std::unique_ptr<MathTask> _currentLevel;
        const char* _endScreenTitle{"Game Over"};
        const char* _endScreenText;

        void nextLevel();
        void showEndScreen();
    };
}

#endif // ATHENA_CALC_H
