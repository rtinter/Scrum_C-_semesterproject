#include "Game.hpp"

namespace abstract_game {

    Game::Game(GameID gameID) :_gameID(gameID) {

    }

    void Game::stop() {
        reset();
    }

// TODO: call this function when the user will be returned to the main menu
    void Game::sendSessionInfo() {

        // TODO: use the information of the game session and save it somewhere
    }

//TODO call this function when the user has completed a run (e. g. when result overlay is shown)
    void Game::saveRunThroughResult(std::string const &resultUnit, long const &result) {
        _gameSession->addNewGameRunThrough(resultUnit, result);
    }

    std::string Game::getName() const {
        return _gameName;
    }

    std::shared_ptr<GameSession> Game::getGameSession() {
        return _gameSession;
    }

}