#ifndef EQUATION_BUILDER_HPP
#define EQUATION_BUILDER_HPP

#include "MathTask.hpp"
#include <vector>
#include <string>
#include <random>  // Include necessary for std::mt19937
#include "SoundPolice.hpp"

/**
 * @brief A class that generates and handles an equation building task.
 */
class EquationBuilder : public MathTask {
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
    char _input[128];

    void generateTask();
    bool evaluateUserInput();
    int evaluateExpression() const;
};

#endif //EQUATION_BUILDER_HPP
