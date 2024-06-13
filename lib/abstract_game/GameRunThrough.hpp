//
// Created by karlinaj on 30.05.2024.
//

#ifndef ATHENA_GAMERUNTHROUGH_HPP
#define ATHENA_GAMERUNTHROUGH_HPP

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
        long result;
        std::string resultUnit;

        GameRunThrough(size_t const &gameSessionUID, int const &gameRunThroughUID, std::string const &resultUnit,
                       long const &result);

    };

} // abstract_game

#endif //ATHENA_GAMERUNTHROUGH_HPP
