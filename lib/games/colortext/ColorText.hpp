#pragma once

#include "Game.hpp"

namespace games {
    class ColorText : Game {
    public:
        using Game::Game;
        void reset() override;
        void start() override;
        void stop() override;
    };
}