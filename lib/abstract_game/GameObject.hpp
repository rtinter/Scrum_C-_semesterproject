#pragma once

#include <imgui.h>

namespace abstract_game {
    /**
     * @brief The GameObject class is an abstract base class for game objects.
     *
     * This class defines the interface for game objects in a game.
     * It provides methods for rendering the game object and getting its coordinates.
     */
    class GameObject {
    protected:
        float _x, _y, _z;

    public:
        virtual ~GameObject() = default;

        explicit GameObject(float x, float y, float z);

        virtual void render() const = 0;

        ImVec2 getCoords() const;
    };
} // abstract_game
