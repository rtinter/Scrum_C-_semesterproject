#include "GameFactory.hpp"

std::unique_ptr<Game> GameFactory::createGame(GameType gameType) {
    switch (gameType) {
        case GameType::Reaction:
            return std::make_unique<reaction::Reaction>();
        case GameType::Game2:
            // Return instance of Game2
            // return std::make_unique<Game2>();
        case GameType::Game3:
            // Return instance of Game3
            // return std::make_unique<Game3>();
        default:
            return nullptr;
    }
}
