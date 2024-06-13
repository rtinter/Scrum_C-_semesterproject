#ifndef ATHENA_CALC_H
#define ATHENA_CALC_H

#include <string>
#include "Game.hpp"
#include "Timer.hpp"
#include "Task.hpp"
#include "TaskGenerator.hpp"

namespace games {
    class Calc : public Game {
    private:
        int _currentLevel{1};
        int _currentScore{0};
        int _numberOfCorrectAnswers{0};
        int _numberOfTasks{5};
        int _currentResult{0};
        Task _currentTask;
        TaskGenerator _taskGenerator;
        ui_elements::Timer _taskTimer{"Task Timer", 30};
        ui_elements::Timer _displayTimer{"Display Timer", 4};  // Display timer for showing numbers
        std::chrono::seconds _displayDuration{2};
        enum State { SHOW_START_NUMBER, SHOW_OPERATION, WAIT_FOR_INPUT } _state;

        void generateTask();
        void displayTask();
        void checkAnswer(int playerAnswer);

    public:
        Calc();
        void render() override;
        void renderGame() override;
        void start() override;
        void reset() override;
        void stop() override;
        void updateStatistics() override;
    };
}

#endif // ATHENA_CALC_H
