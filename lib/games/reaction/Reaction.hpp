#ifndef ATHENA_REACTION_H
#define ATHENA_REACTION_H

#include "../../abstract_game/Game.hpp"

namespace games {

    class Reaction : Game {
    public:
        using Game::Game;
        void start() override;
        void reset() override;
        void stop() override;
    };

} // reaction

#endif //ATHENA_REACTION_H
