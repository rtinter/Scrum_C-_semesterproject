#pragma once
#include "imgui.h"

class GameObject {
protected:
    float _x, _y, _z;
public:
    explicit GameObject(float x, float y, float z);
    virtual void render() const = 0;
    ImVec2 getCoords() const;
    float getZ() const {_z;};
};