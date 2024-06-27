// MathTaskFactory.hpp
#ifndef MATH_TASK_FACTORY_HPP
#define MATH_TASK_FACTORY_HPP

#include "MathTask.hpp"
#include "MathTaskType.hpp"
#include <memory>

namespace math_task_factory {
    // Creates a task instance based on the specified type
    std::unique_ptr<MathTask> createMathTask(MathTaskType type);

    // Creates a random task instance
    std::unique_ptr<MathTask> createRandomMathTask();
}

#endif // MATH_TASK_FACTORY_HPP
