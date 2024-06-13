#ifndef ATHENA_SEQUENCE_H
#define ATHENA_SEQUENCE_H

#include "Game.hpp"

namespace sequence {

    class Sequence : public Game {

        std::string _endBoxString;
        int _longestReproducedSequence;

    public:
        Sequence();

        void render() override;

        void renderGame() override;

        void start() override;

        void reset() override;

        void stop() override;

        void updateStatistics() override;

    };

} // sequence

#endif //ATHENA_SEQUENCE_H
