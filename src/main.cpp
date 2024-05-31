#include "App.hpp"
#include "../lib/abstract_game/GameStats.hpp"
#include <iostream>
#include <ctime>

int main() {
    /*GameStats stats;

    // Seed random number generator
    std::srand(std::time(nullptr));

    // Generate random example data
    stats.setStatistic("Kills", std::rand() % 100);
    stats.setStatistic("Deaths", std::rand() % 100);
    stats.setStatistic("Assists", std::rand() % 100);

    // Write statistics to a CSV file
    stats.writeToCsv("game_stats.csv");

    // Clear current statistics
    stats.clearStatistics();

    // Read statistics from the CSV file
    stats.readFromCsv("game_stats.csv");

    // Print statistics to verify
    for (const auto& stat : stats.getAllStatistics()) {
        std::cout << stat.first << ": " << stat.second << std::endl;
    }*/

    App::start();
    return 0;
}
