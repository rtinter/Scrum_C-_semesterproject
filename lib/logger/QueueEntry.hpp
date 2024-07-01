#pragma once

#include <string>

#include "LogType.hpp"

namespace logger {
    struct QueueEntry {
        time_t timestamp;
        std::string content;
        LogType entryType{INFORMATION};
    };
} // logger
