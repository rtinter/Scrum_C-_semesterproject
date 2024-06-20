#ifndef ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP
#define ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP

#include "MathTask.hpp"
#include <random>

/**
 * @brief A class that generates and handles a simple multiplication task.
 */
class SimpleMultiplicationTable : public MathTask {
public:
    explicit SimpleMultiplicationTable(int difficultyLevel = 1);

    void start() override;
    bool isRunning() const override;
    bool wasSuccessfullyCompleted() const override;
    void render() override;
    void setDifficulty(int level) override;

    ~SimpleMultiplicationTable() override = default;

private:
    bool _focusSet;
    int _leftOperand;
    int _rightOperand;
    int _answer;
    bool _running;
    bool _completedSuccessfully;
    int _difficultyLevel;
    std::mt19937 _rng;
    char _input[128];  // Add this line

    void generateTask();
};

#endif //ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP
