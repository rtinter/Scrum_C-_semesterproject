#include "Game.hpp"
#include <iostream>

Game::Game() : _gameSession {GameSession(1, 0)} { }

void Game::setStatistic(const std::string& name, const long& value) {
    //_gameStats.setStatistic(name, value);
}

void Game::stop() {
    updateStatistics();
    reset();
}


void Game::sendSessionInfo(){ // TODO: call this function when the user will be returned to the main menu
    _gameSession.end();

    // TODO: use the information of the game session and save it somewhere
}