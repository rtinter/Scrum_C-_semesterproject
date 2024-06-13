#include "Task.hpp"

Task::Task(int target, const std::vector<std::pair<int, char>>& operations)
        : _target(target), _operations(operations) {}

int Task::getCurrentNumber() const {
    return _operations[_currentIndex].first;
}

char Task::getCurrentOperator() const {
    return _operations[_currentIndex].second;
}

bool Task::hasMoreOperations() const {
    return _currentIndex < _operations.size();
}

bool Task::advance() {
    if (_currentIndex < _operations.size()) {
        int number = _operations[_currentIndex].first;
        char op = _operations[_currentIndex].second;
        _currentResult = arithmetic_utils::performOperation(_currentResult, op, number);
        ++_currentIndex;
        return true;
    }
    return false;
}

int Task::getCurrentResult() const {
    return _currentResult;
}

int Task::getTarget() const {
    return _target;
}
