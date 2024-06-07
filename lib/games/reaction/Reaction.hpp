#pragma once
#include "Game.hpp"

namespace games {

    class Reaction : Game {
    public:
        using Game::Game;
        void start() override;
        void reset() override;
        void stop() override;
    };

} // reaction
