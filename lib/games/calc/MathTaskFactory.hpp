#pragma once

#include <memory>

#include "MathTask.hpp"
#include "MathTaskType.hpp"

namespace calc {
    // Creates a task instance based on the specified type
    std::unique_ptr<MathTask> createMathTask(MathTaskType type);

    // Creates a random task instance
    std::unique_ptr<MathTask> createRandomMathTask();
} // calc
