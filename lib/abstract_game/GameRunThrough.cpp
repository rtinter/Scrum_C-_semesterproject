//
// Created by karlinaj on 30.05.2024.
//

#include "GameRunThrough.h"

GameRunThrough::GameRunThrough(size_t const &gameSessionUID, int const &gameRunThroughUID, std::string const &resultUnit, long const &result)
        : gameSessionUID{gameSessionUID}, gameRunThroughUID{gameRunThroughUID}, resultUnit{resultUnit}, result{result} {

}