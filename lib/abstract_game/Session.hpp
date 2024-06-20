#pragma once

#include <chrono>
#include "GameIDs.hpp"
#include <string>
#include "rapidcsv.h"

struct Session {
    abstract_game::GameID gameId;
    int userId;
    size_t gameSessionId;
    time_t start;
    time_t end;

    std::string date;

    int64_t duration;
    bool ended;
};