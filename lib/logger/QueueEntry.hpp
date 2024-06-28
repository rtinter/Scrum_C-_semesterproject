#pragma once

#include <string>
#include "QueueEntryType.hpp"
#include <chrono>

struct QueueEntry {
    time_t timestamp;
    std::string content;
    QueueEntryType entryType{QueueEntryType::INFORMATION};
};
