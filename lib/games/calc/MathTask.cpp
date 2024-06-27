#include "MathTask.hpp"


void MathTask::initializeRNG() {
    std::random_device rd;
    auto now {std::chrono::system_clock::now()};
    auto duration {now.time_since_epoch()};
    auto timeSeed {std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()};
    std::seed_seq seedSeq{rd(), static_cast<unsigned int>(timeSeed)};
    _rng.seed(seedSeq);
}