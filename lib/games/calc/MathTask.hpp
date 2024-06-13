#ifndef MATH_TASK_HPP
#define MATH_TASK_HPP

#include <string>

/**
 * @brief Abstract base class representing a mathematical task.
 *
 * This class defines the interface for all specific math task implementations.
 * It handles the basic lifecycle of a math task, including checking if the task
 * is running and if it was completed successfully.
 */
class MathTask {
public:
    /**
     * @brief Destructor for MathTask.
     */
    virtual ~MathTask()  = default;

    /**
     * @brief Starts the MathTask.
     */
    virtual void start() const = 0;

    /**
     * @brief Renders the games visuals.
     */
    virtual void render() const = 0;

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
};

#endif // MATH_TASK_HPP
