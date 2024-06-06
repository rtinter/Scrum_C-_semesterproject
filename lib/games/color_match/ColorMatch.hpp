#ifndef ATHENA_COLORMATCH_H
#define ATHENA_COLORMATCH_H

#include <string>
#include "Game.hpp"

namespace color_match {
    class ColorMatch : public Game {
        std::string const _NAME{"Reaction"};

        void start() override;

        void reset() override;
        // void updateStatistics() override;

    public:
        void render();
    };
}

#endif //ATHENA_COLORMATCH_H
