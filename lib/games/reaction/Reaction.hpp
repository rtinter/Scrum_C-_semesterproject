#pragma once
#include "Game.hpp"
#include "string"

namespace games {

    class Reaction : abstract_game::Game {
        //init to test function without the game implementation
        std::string _name {"Reaction"};
    public:
        using Game::Game;
        void start() override;
        void reset() override;
        void stop() override;
        std::string getName() const ;
    };

} // reaction
