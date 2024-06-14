#ifndef ATHENA_CALC_H
#define ATHENA_CALC_H

#include <string>
#include "Game.hpp"
#include "MathTask.hpp"
#include "MathTaskFactory.hpp"
#include <memory>
#include <chrono>

namespace games {
    class Calc : public abstract_game::Game {
    public:
        Calc();
        void start() override;
        void render() override;
        std::string getName() const override;
        void reset() override;
        void stop() override;

    private:
        int _completedLevels{0};
        bool _elapsedTimeSet{false};
        bool _showEndbox{false};
        std::string _endScreenTitle;
        std::string _endScreenStatisticText;
        std::chrono::steady_clock::time_point _startTime;
        std::chrono::steady_clock::time_point _endTime;
        double _elapsedTimeCalculated{0.0};
        std::unique_ptr<MathTask> _currentLevel;

        void nextLevel();
        void renderGame() override;
        void showEndScreen();
        void calculateEndScreenText();
        double getElapsedTimeInMinutes() const;
        void updateStatistics() override;
    };
}

#endif // ATHENA_CALC_H
