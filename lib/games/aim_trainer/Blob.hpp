#pragma once
#include "imgui.h"
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

namespace aim_trainer {
class Blob : public GameObject {
private:
    float _radius {30.0};
    ImVec4 _color{};
public:
    Blob(float x, float y, float z);
    float getRadius() const {return _radius;};
    void render() const override;
    void decrease(float percentage);
    bool canBeDisposed() const { return _radius < 2.0;};
};
}