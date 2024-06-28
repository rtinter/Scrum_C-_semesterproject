#pragma once

#include <string>

/**
 * @brief Abstract base class representing a scene in the application.
 */
class Scene {
public:
    /**
     * @brief Virtual destructor to allow derived classes to clean up resources.
     */
    virtual ~Scene() = default;

    /**
     * @brief Pure virtual method to render the scene. Must be implemented by derived classes.
     */
    virtual void render() = 0;

    /**
     * @brief Pure virtual method to get the name of the scene. Must be implemented by derived classes.
     * @return The name of the scene as a string.
     */
    virtual std::string getName() const = 0;
};
