#pragma once

#include <random>

#include "MathTask.hpp"

namespace calc {
    /**
     * @brief A class that generates and handles a simple multiplication task.
     */
    class SimpleMultiplicationTable final : public MathTask {
    public:
        SimpleMultiplicationTable();

        void start() override;

        bool isRunning() const override;

        bool wasSuccessfullyCompleted() const override;

        void render() override;

    private:
        int _leftOperand;
        int _rightOperand;
        int _answer;
        std::vector<char> _input;

        void generateTask();
    };
} // calc
