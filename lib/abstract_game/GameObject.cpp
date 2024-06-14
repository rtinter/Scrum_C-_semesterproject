#include "GameObject.hpp"

GameObject::GameObject(float x, float y, float z) : _x{x}, _y{y}, _z{z}{
}

ImVec2 GameObject::getCoords() const {
    return {_x, _y};
}
