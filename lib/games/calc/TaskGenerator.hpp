#ifndef TASKGENERATOR_H
#define TASKGENERATOR_H

#include "Task.hpp"
#include <vector>
#include <map>
#include <utility> // Für std::pair

class TaskGenerator {
public:
    TaskGenerator();
    Task generateTask(int levelIndex, int currentResult);

private:
    std::vector<std::map<char, std::pair<int, int>>> _levels;
    void initializeLevels();
    std::map<char, std::pair<int, int>> getLevelConfig(int levelIndex);

    static int adjustValueForCurrentResult(char op, int value, int currentResult);
};

#endif // TASKGENERATOR_H
