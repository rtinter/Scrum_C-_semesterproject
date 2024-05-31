#pragma once
#include "Reaction.hpp"
#include <memory>

class GameFactory {
public:
    enum class GameType {
        Reaction,
        Game2,
        Game3,
        // Add more game types here
    };

    static std::unique_ptr<Game> createGame(GameType gameType);
};
