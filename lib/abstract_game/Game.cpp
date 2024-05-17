#include "Game.hpp"
#include <iostream>

Game::Game() {}

void Game::setStatistic(const std::string& name, const long& value) {
    gameStats.setStatistic(name, value);
}

void Game::stop() {
    updateStatistics();
    sendStatistics();
}

void Game::sendStatistics() {
    // placeholder for actual data sending
    const auto& stats = gameStats.getAllStatistics();

    for (const auto& pair : stats) {
        std::cout << "Uploading: " << gameUUID << ", " << gameID << ", " << userID
            << ", " << pair.first << ": " << pair.second << std::endl;
    }
}
