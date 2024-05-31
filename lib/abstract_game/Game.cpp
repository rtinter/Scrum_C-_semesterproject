#include "Game.hpp"
#include <iostream>

Game::Game() : _gameID{1}, _gameSession {GameSession(1, 0)} { } //TODO make gameID and userID dynamic

/*void Game::setStatistic(const std::string& name, const long& value) {
    _gameStats.setStatistic(name, value);
}*/

void Game::stop() {
    /*updateStatistics();
    sendStatistics();*/
    reset();
}

/*void Game::sendStatistics() {
    // placeholder for actual data sending
    const auto& stats = _gameStats.getAllStatistics();

    for (const auto& pair : stats) {
        std::cout << "Uploading: " << _gameSession.getGameSessionUID() << ", " << _gameSession.getGameID() << ", " << _gameSession.getUserID()
            << ", " << pair.first << ": " << pair.second << std::endl;
    }
}*/

void Game::sendSessionInfo(){ // TODO: call this function when the user will be returned to the main menu
    _gameSession.end();

    // TODO: use the information of the game session and save it somewhere
}

void Game::saveRunThroughResult(std::string const &resultUnit, long const &result) {    //TODO call this function when the user has completed a run (e. g. when result overlay is shown)
    _gameSession.addNewGameRunThrough(resultUnit, result);
}