//
// Created by karlinaj on 30.05.2024.
//

#ifndef ATHENA_GAMERUNTHROUGH_H
#define ATHENA_GAMERUNTHROUGH_H

#include <string>

struct GameRunThrough {

    int gameRunThroughUid;
    int gameSessionUid;
    long result;
    std::string resultUnit;

    GameRunThrough(int const &gameSessionUid, std::string const &resultUnit, long const &result);

    int generateGameRunThroughUid();

};


#endif //ATHENA_GAMERUNTHROUGH_H
