#pragma once

#include <imgui.h>

namespace abstract_game {
    /**
     * @brief Abstract base class representing a generic game object.
     *
     * This class provides the interface and basic functionality for game objects.
     * Derived classes must implement the render method to define how the object is displayed.
     */
    class GameObject {
    protected:
        float _x, _y, _z; ///< The coordinates of the game object.

    public:
        virtual ~GameObject() = default;

        /**
         * @brief Constructor to initialize the game object with coordinates.
         *
         * @param x The x-coordinate of the game object.
         * @param y The y-coordinate of the game object.
         * @param z The z-coordinate of the game object.
         */
        explicit GameObject(float x, float y, float z);

        /**
         * @brief Renders the game object.
         *
         * This pure virtual method must be implemented by derived classes to define how the object is displayed.
         */
        virtual void render() const = 0;

        /**
         * @brief Gets the coordinates of the game object.
         *
         * @return An ImVec2 containing the x and y coordinates of the game object.
         */
        ImVec2 getCoords() const;
    };
} // abstract_game
