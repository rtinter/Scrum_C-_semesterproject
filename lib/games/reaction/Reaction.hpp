#pragma once

#include "Game.hpp"
#include "string"

namespace games {

    class Reaction : Game {
        //init to test function without the game implementation
        std::string _name{"Reaktionsspiel"};
    public:
        using Game::Game;

        void start() override;

        void reset() override;

        void stop() override;

        std::string getName() const override;
    };

} // reaction
