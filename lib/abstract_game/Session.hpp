#pragma once

#include <chrono>
#include "GameIDs.hpp"
#include <string>
#include "rapidcsv.h"

struct Session {
    abstract_game::GameID gameId;
    int userId;
    size_t gameSessionId;
    std::chrono::steady_clock::time_point startPoint;
    std::chrono::steady_clock::time_point endPoint;
    unsigned long long duration;
    bool ended;
};