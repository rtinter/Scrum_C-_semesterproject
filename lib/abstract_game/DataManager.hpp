//
// Created by Admin on 06.06.2024.
//

#ifndef ATHENA_DATAMANAGER_HPP
#define ATHENA_DATAMANAGER_HPP

#include <string>
#include <memory>
#include <vector>
#include "GameIDs.hpp"
#include "Session.hpp"


namespace abstract_game {

    class DataManager {
    public:
        virtual ~DataManager() = default;
        /**
         * @brief Load the game session data from a CSV file.
         *
         * This method loads the game session data from a CSV file.
         *
         * @param filename The name of the CSV file.
         */
        virtual void saveGameSession(size_t sessionUID, int userID, GameID gameID,
                                     long long startTime, long long endTime,
                                     unsigned long long duration, bool ended) = 0;

        virtual std::vector<Session> getUserData(int UserID) = 0;
    };

} // abstract_game

#endif //ATHENA_DATAMANAGER_HPP
