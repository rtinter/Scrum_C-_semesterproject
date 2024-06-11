#ifndef TASK_H
#define TASK_H

#include <vector>
#include <utility>

class Task {
public:
    /**
     * @brief Konstruktor, der eine Folge von Zahlen und Operatoren erhält.
     * @param operations Vektor von Paaren, die eine Zahl und einen Operator enthalten.
     */
    Task(const std::vector<std::pair<int, char>>& operations);

    int getCurrentNumber() const;
    char getCurrentOperator() const;
    bool hasMoreOperations() const;
    void advance();
    int getCurrentResult() const;

private:
    std::vector<std::pair<int, char>> _operations;
    size_t _currentIndex{0};
    int _currentResult{0};
};

/*
 Beispiel einer Task:
 _operations: { {1, '+'}, {2, '-'}, {3, '*'}, {4, '/'} }
 */

#endif // TASK_H
