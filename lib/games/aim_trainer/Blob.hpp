#pragma once

#include <imgui.h>

#include "GameObject.hpp"

namespace aim_trainer {
    /**
     * @brief The Blob class represents a single blob in the aim trainer game.
     *
     * This class represents a single blob in the aim trainer game.
     * It inherits from the GameObject class and provides methods for rendering the blob and checking if it can be disposed.
     */
    class Blob final : public abstract_game::GameObject {
        float _radius{120.0};
        ImVec4 _color;

    public:
        Blob(float x, float y, float z);

        float getRadius() const { return _radius; };

        void render() const override;

        void decrease(float percentage);

        bool canBeDisposed() const { return _radius < 10.0; };
    };
} // aim_trainer
