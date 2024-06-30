#include "GameObject.hpp"

namespace abstract_game {
    GameObject::GameObject(float const x, float const y, float const z) : _x{x}, _y{y}, _z{z} {
    }

    ImVec2 GameObject::getCoords() const {
        return {_x, _y};
    }
} // abstract_game
