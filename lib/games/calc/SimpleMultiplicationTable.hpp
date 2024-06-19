#ifndef ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP
#define ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP

#include "MathTask.hpp"
#include <random>

/**
 * @brief A class that generates and handles a simple multiplication task.
 */
class SimpleMultiplicationTable : public MathTask {
public:
    SimpleMultiplicationTable();

    void start() override;
    bool isRunning() const override;
    bool wasSuccessfullyCompleted() const override;
    void render() override;
    void setDifficulty(int level) override;

private:
    bool _focusSet{false};
    int _leftOperand;
    int _rightOperand;
    int _answer;
    bool _running;
    bool _completedSuccessfully;
    int _difficultyLevel;
    std::mt19937 _rng;

    int _score;
    int _streak;

    void generateTask();
};

#endif //ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP
