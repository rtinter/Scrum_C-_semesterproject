#ifndef ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP
#define ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP

#include "MathTask.hpp"
#include <random>
#include "SoundPolice.hpp"

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

private:
    int _leftOperand;
    int _rightOperand;
    int _answer;
    char _input[128];

    void generateTask();
};

#endif //ATHENA_SIMPLE_MULTIPLICATION_TABLE_HPP
