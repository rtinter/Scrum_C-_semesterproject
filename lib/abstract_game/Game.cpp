#include "Game.hpp"

namespace abstract_game {

    Game::Game(GameID gameID) :_gameID(gameID) {

    }

    void Game::stop() {
        reset();
    }


    std::string Game::getName() const {
        return _gameName;
    }


}