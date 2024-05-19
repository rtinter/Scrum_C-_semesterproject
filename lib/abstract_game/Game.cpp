#include "Game.hpp"
#include <iostream>

void Game::setStatistic(const std::string& name, const long& value) {
    _gameStats.setStatistic(name, value);
}

void Game::stop() {
    updateStatistics();
    _sendStatistics();
}

void Game::_sendStatistics() {
    // placeholder for actual data sending
    const auto& stats = _gameStats.getAllStatistics();

    for (const auto& pair : stats) {
        std::cout << "Uploading: " << _gameUUID << ", " << _gameID << ", " << _userID
            << ", " << pair.first << ": " << pair.second << std::endl;
    }
}
