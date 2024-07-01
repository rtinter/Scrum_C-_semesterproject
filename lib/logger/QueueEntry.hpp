#pragma once

#include <string>

#include "LogType.hpp"

struct QueueEntry {
    time_t timestamp;
    std::string content;
    LogType entryType{LogType::INFORMATION};
};
