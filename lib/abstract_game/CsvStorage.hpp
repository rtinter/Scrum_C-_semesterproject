//
// Created by Admin on 06.06.2024.
//

#ifndef ATHENA_CSVSTORAGE_HPP
#define ATHENA_CSVSTORAGE_HPP


#include <iostream>
#include "DataManager.hpp"
#include "Session.hpp"

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
                unsigned long long duration,
                bool ended
        ) override;

        void saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) override;
        std::vector<Session> getUserData(int userID) override;
    };

} // abstract_game

#endif //ATHENA_CSVSTORAGE_HPP
