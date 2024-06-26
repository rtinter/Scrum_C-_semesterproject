#ifndef CALC_HPP
#define CALC_HPP

#include <string>
#include <chrono>
#include <optional>
#include "Game.hpp"
#include "Timer.hpp"
#include "MathTask.hpp"

namespace games {
    class Calc : public abstract_game::Game {
    public:
        Calc();

        void render() override;
        void start() override;
        void reset() override;
        void stop() override;
        void updateStatistics() override;
        std::string getName() const override;

    private:
        void nextLevel();
        void renderGame() override;
        void showEndScreen();
        void calculateEndScreenText();
        double getElapsedTimeInSeconds() const;

        int _difficulty_level;
        int _completedLevels;
        bool _showEndbox;
        bool _showInfobox;

        // capture spend time in game for end screen
        std::optional<std::chrono::steady_clock::time_point> _startTime;
        std::optional<std::chrono::steady_clock::time_point> _endTime;
        double _elapsedTimeCalculated;

        std::string _endScreenTitle;
        std::string _endScreenStatisticText;
        std::string _averageTimeText;
        std::shared_ptr<MathTask> _currentLevel;
        ui_elements::Timer _timer;
        int _timerSeconds; // Initialize with 10 seconds
    };
}

#endif // CALC_HPP
