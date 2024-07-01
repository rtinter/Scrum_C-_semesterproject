#pragma once

#include <random>  // Include necessary for std::mt19937
#include <string>
#include <vector>

#include "MathTask.hpp"

namespace calc {
    /**
     * @brief A class that generates and handles an equation building task.
     */
    class EquationBuilder final : public MathTask {
    public:
        EquationBuilder();

        void start() override;

        bool isRunning() const override;

        bool wasSuccessfullyCompleted() const override;

        void render() override;

    private:
        enum class Operator { ADD, SUBTRACT, MULTIPLY, DIVIDE };

        int _targetNumber;
        std::string _operator;
        int _number;
        std::vector<char> _input;

        void generateTask();

        bool evaluateUserInput() const;

        int evaluateExpression() const;
    };
} // calc
