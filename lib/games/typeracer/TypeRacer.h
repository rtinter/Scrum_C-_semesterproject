#ifndef ATHENA_TYPERACER_H
#define ATHENA_TYPERACER_H

#include "Game.hpp"

namespace typeracer {

    class TypeRacer : public Game {
    public:
        explicit TypeRacer();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getName() const override;
    };

} // typeracer

#endif //ATHENA_TYPERACER_H
