#ifndef TASK_GENERATOR_HPP
#define TASK_GENERATOR_HPP

#include "Task.hpp"
#include <vector>
#include <map>
#include <random>

class TaskGenerator {
public:
    TaskGenerator();

    /**
     * @brief Generiert eine Task für das gegebene Level und Ziel.
     * @param levelIndex Der Index des Levels.
     * @param target Das Ziel, das erreicht werden soll.
     * @return Eine generierte Task.
     */
    Task generateTask(int levelIndex, int target) const;

private:
    std::vector<std::map<char, std::pair<int, int>>> _levels;
    mutable std::default_random_engine _generator;

    /**
     * @brief Initialisiert die Levelkonfigurationen.
     */
    void initializeLevels();

    /**
     * @brief Holt die Konfiguration des Levels.
     * @param levelIndex Der Index des Levels.
     * @return Die Levelkonfiguration als std::map.
     */
    std::map<char, std::pair<int, int>> getLevelConfig(int levelIndex) const;
};

#endif // TASK_GENERATOR_HPP
