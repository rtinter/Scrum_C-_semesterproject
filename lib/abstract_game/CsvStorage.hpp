#pragma once

#include <iostream>
#include "DataManager.hpp"
#include "Session.hpp"

namespace abstract_game {

    class CsvStorage : public DataManager {
    public:

        void saveGameSession(size_t sessionUID, int userID, GameID gameID,
                             long long startTime, long long endTime,
                             unsigned long long duration, bool ended) override;

        std::vector<Session> getUserData(int userID) override;
    };

} // abstract_game
