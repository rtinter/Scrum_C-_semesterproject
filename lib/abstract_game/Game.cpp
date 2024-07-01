#include "Game.hpp"

namespace abstract_game {
    Game::Game(GameID const gameID) : _gameID(gameID), _statisticResult(0) {
    }

    void Game::stop() {
        reset();
    }

    std::string Game::getName() const {
        return _gameName;
    }
} // abstract_game
