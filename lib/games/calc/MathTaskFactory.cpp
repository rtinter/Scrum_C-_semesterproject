// MathTaskFactory.cpp
#include "MathTaskFactory.hpp"
#include "SimpleMultiplicationTable.hpp"
#include "EquationBuilder.hpp"
#include <random>
#include <chrono>
#include <stdexcept>

namespace math_task_factory {

    std::unique_ptr<MathTask> createMathTask(MathTaskType type) {
        switch (type) {
            case MathTaskType::SIMPLE_MULTIPLICATION_TABLE:
                return std::make_unique<EquationBuilder>();
            case MathTaskType::EQUATION_BUILDER:
                return std::make_unique<EquationBuilder>();
            default:
                throw std::invalid_argument("Unsupported MathTaskType");
        }
    }

    std::unique_ptr<MathTask> createRandomMathTask() {
        // Get current time as seed
        auto now {std::chrono::system_clock::now()};
        auto duration {now.time_since_epoch()};
        auto timeSeed {std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()};

        std::random_device rd;
        std::seed_seq seedSeq{rd(), static_cast<unsigned int>(timeSeed)};
        std::mt19937 gen(seedSeq);

        // Create a uniform distribution from 0 to the last enum value (excluding Count)
        std::uniform_int_distribution<> dis(0, static_cast<int>(MathTaskType::EQUATION_BUILDER));

        auto randomType {static_cast<MathTaskType>(dis(gen))};
        return createMathTask(randomType);
    }
}