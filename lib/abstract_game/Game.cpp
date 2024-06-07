#include "Game.hpp"
#include <iostream>

namespace abstract_game {

    Game::Game(GameID gameID) : _gameID{gameID}, _gameSession{static_cast<int>(gameID),1} {}

    void Game::stop() {
        reset();
    }

    void Game::sendSessionInfo() { // TODO: call this function when the user will be returned to the main menu
        _gameSession.end();

        // TODO: use the information of the game session and save it somewhere
    }

    void Game::saveRunThroughResult(std::string const &resultUnit,
                                    long const &result) {    //TODO call this function when the user has completed a run (e. g. when result overlay is shown)
        _gameSession.addNewGameRunThrough(resultUnit, result);
    }

    GameID Game::getGameID() const {
        return _gameID;
    }

}