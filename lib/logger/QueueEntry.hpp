#pragma once

#include <string>

#include "QueueEntryType.hpp"

namespace logger {
    struct QueueEntry {
        time_t timestamp;
        std::string content;
        QueueEntryType entryType{INFORMATION};
    };
} // logger
