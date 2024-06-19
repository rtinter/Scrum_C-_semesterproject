#ifndef CALC_HPP
#define CALC_HPP

#include <string>
#include <chrono>
#include <optional>
#include "../abstract_game/Game.hpp"
#include "../ui_elements/Timer.hpp"
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
        void nextLevel(int difficulty_level);
        void renderGame() override;
        void showEndScreen();
        void calculateEndScreenText();
        double getElapsedTimeInSeconds() const;

        int _difficulty_level{1};
        int _completedLevels{0};
        bool _showEndbox{false};
        bool _showInfobox{true};
        std::optional<std::chrono::steady_clock::time_point> _startTime;
        std::optional<std::chrono::steady_clock::time_point> _endTime;
        double _elapsedTimeCalculated{0.0};
        std::string _endScreenTitle;
        std::string _endScreenStatisticText;
        std::string _averageTimeText;
        std::shared_ptr<MathTask> _currentLevel;
    };
}

#endif // CALC_HPP
