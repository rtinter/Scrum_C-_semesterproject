//
// Created by karlinaj on 30.05.2024.
//

#include "GameRunThrough.h"

GameRunThrough::GameRunThrough(const int &gameSessionUid, const std::string &resultUnit, const long &result)
        : gameSessionUid{gameSessionUid}, resultUnit{resultUnit}, result{result} {

    gameRunThroughUid = generateGameRunThroughUid();

}