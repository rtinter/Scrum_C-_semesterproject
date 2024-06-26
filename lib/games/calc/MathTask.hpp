#ifndef MATH_TASK_HPP
#define MATH_TASK_HPP

#include <string>
#include <random>
#include <chrono>

/**
 * @brief Abstract base class representing a mathematical task.
 *
 * This class defines the interface for all specific math task implementations.
 * It handles the basic lifecycle of a math task, including checking if the task
 * is running and if it was completed successfully.
 */
class MathTask {
public:

    // Helper vars for internal state handling of games
    bool _focusSet;
    bool _running;
    bool _completedSuccessfully;
    std::mt19937 _rng;
    /**
     * @brief Destructor for MathTask.
     */
    virtual ~MathTask() = default;

    /**
     * @brief Starts the MathTask.
     */
    virtual void start() = 0;

    /**
     * @brief Renders the games visuals.
     */
    virtual void render() = 0;

    /**
     * @brief Checks if the math task is currently running.
     * @return True if the math task is running, false otherwise.
     */
    virtual bool isRunning() const = 0;

    /**
     * @brief Checks if the math task was completed successfully.
     * @return True if the math task was successful, false otherwise.
     */
    virtual bool wasSuccessfullyCompleted() const = 0;

    void initializeRNG();
};

#endif // MATH_TASK_HPP
