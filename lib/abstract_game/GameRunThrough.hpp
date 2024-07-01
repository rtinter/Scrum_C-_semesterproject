#pragma once

#include <string>

namespace abstract_game {
    /**
     * @brief Struct for holding GameRunThrough information.
     *
     * This struct stores the information of a single runthrough of a game during a gamesession.
     */
    struct GameRunThrough {
        int gameRunThroughUID;
        size_t gameSessionUID;
        double result;
        std::string resultUnit;

        GameRunThrough(size_t const &gameSessionUID, int const &gameRunThroughUID, std::string const &resultUnit,
                       double const &result);
    };
} // abstract_game
