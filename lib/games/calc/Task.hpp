#ifndef TASK_H
#define TASK_H

#include <vector>
#include <utility>
#include "ArithmeticUtils.hpp"

class Task {
public:
    Task(int target, const std::vector<std::pair<int, char>>& operations);

    int getCurrentNumber() const;
    char getCurrentOperator() const;
    bool hasMoreOperations() const;
    bool advance();
    int getCurrentResult() const;
    int getTarget() const;

private:
    std::vector<std::pair<int, char>> _operations;
    size_t _currentIndex{0};
    int _currentResult{0};
    int _target;
};

#endif // TASK_H
