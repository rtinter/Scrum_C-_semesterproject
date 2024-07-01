#ifndef ATHENA_CSVSTORAGE_HPP
#define ATHENA_CSVSTORAGE_HPP


#include <iostream>
#include "DataManager.hpp"
#include <chrono>

namespace abstract_game {

    class CsvStorage : public DataManager {
    public:
        void saveGameSession(
                size_t sessionUID,
                int userID,
                GameID gameID,
                time_t start,
                time_t end,
                bool ended
        ) override;

        static std::string getDateString(time_t timestamp);
        void saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) override;
    };

} // abstract_game

#endif //ATHENA_CSVSTORAGE_HPP
