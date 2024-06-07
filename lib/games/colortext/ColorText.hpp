#pragma once

#include "Game.hpp"

namespace games {
    class ColorText : Game {
        std::string _name { "Farbe und Text" };
    public:
        using Game::Game;
        void reset() override;
        void start() override;
        void stop() override;

        std::string getName() const override;
    };
}