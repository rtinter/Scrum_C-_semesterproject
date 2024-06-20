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
    explicit EquationBuilder(int difficultyLevel);

    void start() override;
    bool isRunning() const override;
    bool wasSuccessfullyCompleted() const override;
    void render() override;
    void setDifficulty(int level) override;

private:
    bool _focusSet{false};
    int _targetNumber;
    std::vector<std::string> _operators;
    std::vector<int> _numbers;
    std::vector<std::string> _inputBuffers;  // For user inputs
    bool _running;
    bool _completedSuccessfully;
    int _difficultyLevel;
    std::mt19937 _rng;

    void generateTask();
    bool evaluateUserInput();
    bool isSolvable() const;
    int evaluateExpression() const; // New method for expression evaluation
};

#endif //EQUATION_BUILDER_HPP
