#include "TaskGenerator.hpp"
#include "../commons/RandomPicker.hpp"
#include <ctime>

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

std::map<char, std::pair<int, int>> TaskGenerator::getLevelConfig(int levelIndex) {
    if (levelIndex < _levels.size()) {
        return _levels[levelIndex];
    }

    std::map<char, std::pair<int, int>> lastLevelConfig = _levels.back();
    for (auto& entry : lastLevelConfig) {
        entry.second.first *= 1.1; // Erhöhen des Minimalwerts um 10%
        entry.second.second *= 1.1; // Erhöhen des Maximalwerts um 10%
    }
    return lastLevelConfig;
}

int TaskGenerator::adjustValueForCurrentResult(char op, int value, int currentResult) {
    if (op == '*' || op == '/') {
        // Vermeide große Multiplikationen und Divisionen, wenn das aktuelle Ergebnis bereits groß ist
        if (currentResult > 20) {
            return std::min(value, 5); // Begrenze die Zahl auf maximal 10
        }
    }
    return value;
}

Task TaskGenerator::generateTask(int levelIndex, int currentResult) {
    std::map<char, std::pair<int, int>> levelConfig = getLevelConfig(levelIndex);

    std::vector<std::pair<int, char>> operations;

    for (int i = 0; i < 5; ++i) {
        char op = commons::RandomPicker::pickRandomElement(std::vector<char>{'+', '-', '*', '/'});
        std::uniform_int_distribution<int> numDistribution(levelConfig[op].first, levelConfig[op].second);
        std::default_random_engine generator(static_cast<unsigned int>(time(0)));
        int num = numDistribution(generator);

        num = adjustValueForCurrentResult(op, num, currentResult);

        if (op == '/' && num != 0 && i > 0 && currentResult % num != 0) {
            num = 1; // Sicherstellen, dass wir keine Dezimalzahlen erhalten
        }

        operations.emplace_back(num, op);

        // Aktualisiere das aktuelle Ergebnis mit der neuen Operation
        Task tempTask(operations);
        tempTask.advance();
        currentResult = tempTask.getCurrentResult();
    }

    return Task(operations);
}
