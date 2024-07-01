#include "MathTask.hpp"

#include <chrono>


namespace calc {
    void MathTask::initializeRNG() {
        std::random_device rd;
        auto const now{std::chrono::system_clock::now()};
        auto const duration{now.time_since_epoch()};
        auto const timeSeed{std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()};
        std::seed_seq seedSeq{rd(), static_cast<unsigned int>(timeSeed)};
        _rng.seed(seedSeq);
    }
} // calc
