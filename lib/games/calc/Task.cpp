#include "Task.hpp"

Task::Task(const std::vector<std::pair<int, char>>& operations)
        : _operations(operations) {
    _currentResult = 0; // Startwert für Berechnung
}

int Task::getCurrentNumber() const {
    return _operations[_currentIndex].first;
}

char Task::getCurrentOperator() const {
    return _operations[_currentIndex].second;
}

bool Task::hasMoreOperations() const {
    return _currentIndex < _operations.size();
}

void Task::advance() {
    if (_currentIndex < _operations.size()) {
        int number = _operations[_currentIndex].first;
        char op = _operations[_currentIndex].second;
        switch (op) {
            case '+': _currentResult += number; break;
            case '-': _currentResult -= number; break;
            case '*': _currentResult *= number; break;
            case '/': _currentResult /= number; break;
            case '%': _currentResult %= number; break;
            default: break; // Füge eine Default-Anweisung hinzu
        }
        ++_currentIndex;
    }
}

int Task::getCurrentResult() const {
    return _currentResult;
}
