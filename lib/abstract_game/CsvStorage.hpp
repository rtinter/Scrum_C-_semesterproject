//
// Created by Admin on 06.06.2024.
//

#ifndef ATHENA_CSVSTORAGE_HPP
#define ATHENA_CSVSTORAGE_HPP


#include <iostream>
#include "DataManager.hpp"
#include "Session.hpp"
#include <chrono>

namespace abstract_game {

    class CsvStorage : public DataManager {
    public:
        void saveGameSession(
                size_t sessionUID,
                int userID,
                GameID gameID,
                long long startTime,
                long long endTime,
                time_t start,
                time_t end,
                bool ended
        ) override;

        std::string getDateString(time_t timestamp);
        void saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) override;
        std::vector<Session> getUserData(int userID) override;
    };

} // abstract_game

#endif //ATHENA_CSVSTORAGE_HPP
