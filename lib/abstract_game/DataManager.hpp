//
// Created by Admin on 06.06.2024.
//

#ifndef ATHENA_DATAMANAGER_HPP
#define ATHENA_DATAMANAGER_HPP

#include <string>
#include <memory>
#include <vector>
#include "GameIDs.hpp"
#include "GameRunThrough.hpp"


namespace abstract_game {

    class DataManager {
    public:
        virtual ~DataManager() = default;

        virtual void saveGameSession(size_t sessionUID, int userID, GameID gameID,
                                     long long startTime, long long endTime,
                                     unsigned long long duration, bool ended) = 0;

        virtual void saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) = 0;

        virtual void getUserData(int UserID) = 0;

    };

} // abstract_game

#endif //ATHENA_DATAMANAGER_HPP
