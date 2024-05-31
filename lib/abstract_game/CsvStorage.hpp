//
// Created by Admin on 31.05.2024.
//

#ifndef ATHENA_CSVSTORAGE_HPP
#define ATHENA_CSVSTORAGE_HPP

#include <iostream>
#include "DataManager.hpp"

class CsvStorage : public DataManager {
public:
    void saveGameSession(size_t sessionUID, int userID, int gameID,
                         long long startTime, long long endTime,
                         unsigned long long duration, bool ended) override;

    void getUserData(int userID) override;
};


#endif //ATHENA_CSVSTORAGE_HPP
