#include "TaskGenerator.hpp"
#include "../commons/RandomPicker.hpp"

TaskGenerator::TaskGenerator() {
    initializeLevels();
}

void TaskGenerator::initializeLevels() {
    _levels.emplace_back(std::map<char, std::pair<int, int>>{
            {'+', {1, 20}},
            {'-', {1, 20}}
    });
    _levels.emplace_back(std::map<char, std::pair<int, int>>{
            {'+', {1, 50}},
            {'-', {1, 50}},
            {'*', {1, 10}}
    });
    _levels.emplace_back(std::map<char, std::pair<int, int>>{
            {'+', {1, 100}},
            {'-', {1, 100}},
            {'*', {1, 10}},
            {'/', {1, 10}}
    });
    _levels.emplace_back(std::map<char, std::pair<int, int>>{
            {'+', {1, 200}},
            {'-', {1, 200}},
            {'*', {1, 15}},
            {'/', {1, 15}}
    });
    _levels.emplace_back(std::map<char, std::pair<int, int>>{
            {'+', {1, 500}},
            {'-', {1, 500}},
            {'*', {1, 20}},
            {'/', {1, 20}}
    });
}

std::map<char, std::pair<int, int>> TaskGenerator::getLevelConfig(int levelIndex) const {
    if (levelIndex < _levels.size()) {
        return _levels[levelIndex];
    }

    std::map<char, std::pair<int, int>> lastLevelConfig = _levels.back();
    for (auto& entry : lastLevelConfig) {
        entry.second.first = static_cast<int>(entry.second.first * 1.1); // Erhöhen des Minimalwerts um 10%
        entry.second.second = static_cast<int>(entry.second.second * 1.1); // Erhöhen des Maximalwerts um 10%
    }
    return lastLevelConfig;
}

Task TaskGenerator::generateTask(int levelIndex, int target) const {
    std::map<char, std::pair<int, int>> levelConfig = getLevelConfig(levelIndex);

    std::vector<std::pair<int, char>> operations;
    int currentResult = 0;

    for (int i = 0; i < 5; ++i) {
        char op = commons::RandomPicker::pickRandomElement(std::vector<char>{'+', '-', '*', '/'});
        std::uniform_int_distribution<int> numDistribution(levelConfig[op].first, levelConfig[op].second);
        int num = numDistribution(_generator);

        if ((op == '/' || op == '%') && num == 0) {
            num = 1; // Setze den Wert auf 1, um Division durch Null zu vermeiden
        }

        if (op == '/' && num != 0 && currentResult % num != 0) {
            num = 1;
        }

        operations.emplace_back(num, op);
        currentResult = arithmetic_utils::performOperation(currentResult, op, num);
    }

    return Task(target, operations);
}
