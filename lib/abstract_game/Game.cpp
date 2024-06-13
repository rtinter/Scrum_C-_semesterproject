#include "Game.hpp"
#include <iostream>

namespace abstract_game {

    Game::Game() : _gameID{1}, _gameSession{GameSession(1, 0)} {} //TODO make gameID and userID dynamic

void Game::stop() {
    reset();
}

// TODO: call this function when the user will be returned to the main menu
void Game::sendSessionInfo(){
    _gameSession.end();

    // TODO: use the information of the game session and save it somewhere
}

//TODO call this function when the user has completed a run (e. g. when result overlay is shown)
void Game::saveRunThroughResult(std::string const &resultUnit, long const &result) {
    _gameSession.addNewGameRunThrough(resultUnit, result);
}

}