#ifndef ATHENA_CALC_H
#define ATHENA_CALC_H

#include <string>
#include "Game.hpp"
#include "MathTask.hpp"
#include "MathTaskFactory.hpp"
#include <chrono>
#include <optional>

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
        void nextLevel();
        void showEndScreen();
        void calculateEndScreenText();
        double getElapsedTimeInMinutes() const;
        double getElapsedTimeInSeconds() const;
        void updateStatistics() override;
        void renderGame() override;
        bool hasGameEnded() const;
        void handleGameEnd();

        std::unique_ptr<MathTask> _currentLevel;
        int _completedLevels{0};
        bool _showEndbox{false};
        bool _elapsedTimeSet{false};
        double _elapsedTimeCalculated{0.0};
        std::string _endScreenStatisticText;
        std::string _endScreenTitle;
        std::chrono::steady_clock::time_point _startTime;
        std::optional<std::chrono::steady_clock::time_point> _endTime;
    };
}

#endif // ATHENA_CALC_H
