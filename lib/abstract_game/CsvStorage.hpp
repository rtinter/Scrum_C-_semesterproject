//
// Created by Admin on 06.06.2024.
//

#ifndef ATHENA_CSVSTORAGE_HPP
#define ATHENA_CSVSTORAGE_HPP


#include <iostream>
#include "DataManager.hpp"

namespace abstract_game {

    class CsvStorage {
    public:
        void saveGameSession(size_t sessionUID, int userID, int gameID,
                             long long startTime, long long endTime,
                             unsigned long long duration, bool ended) ;

        void getUserData(int userID) ;

    };

} // abstract_game

#endif //ATHENA_CSVSTORAGE_HPP
