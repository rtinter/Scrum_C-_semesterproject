//
// Created by karlinaj on 30.05.2024.
//

#ifndef ATHENA_GAMERUNTHROUGH_H
#define ATHENA_GAMERUNTHROUGH_H

#include <string>

/**
 * Diese Klasse fasst die Daten zusammen, die während eines einzelnen Spieldurchlaufs entstehen.
 * Dazu gehören die UID des Spieldurchlaufs, die UID der zugehörigen Spielsession, das in dem Spieldurchlauf erreichte
 * Ergebnis sowie die Einheit in dem das Ergebnis ausgegeben wird.
 */
struct GameRunThrough {

    int gameRunThroughUid;
    int gameSessionUid;
    long result;
    std::string resultUnit;

    GameRunThrough(int const &gameSessionUid, std::string const &resultUnit, long const &result);

    int generateGameRunThroughUid();

};


#endif //ATHENA_GAMERUNTHROUGH_H
