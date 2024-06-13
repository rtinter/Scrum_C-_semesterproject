#ifndef ATHENA_SEQUENCE_H
#define ATHENA_SEQUENCE_H

#include "Game.hpp"

namespace sequence {

    class Sequence : public Game {
    public:
        void render() override;

        void renderGame() override;

        void start() override;

        void reset() override;

        void updateStatistics() override;

    };

    void Sequence::render() {

    }

    void Sequence::renderGame() {

    }

    void Sequence::start() {

    }

    void Sequence::reset() {

    }

    void Sequence::updateStatistics() {

    }

} // sequence

#endif //ATHENA_SEQUENCE_H
