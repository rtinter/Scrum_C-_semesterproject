//
// Created by karlinaj on 30.05.2024.
//

#ifndef ATHENA_GAMERUNTHROUGH_H
#define ATHENA_GAMERUNTHROUGH_H

#include <string>

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


#endif //ATHENA_GAMERUNTHROUGH_H
