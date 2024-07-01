#include "Blob.hpp"

#include <cstdlib>

namespace aim_trainer {
    Blob::Blob(float const x, float const y, float const z) : GameObject(x, y, z) {
        float r{static_cast<float>((rand() % 255) + 1)};
        float g{static_cast<float>((rand() % 255) + 1)};
        float b{static_cast<float>((rand() % 255) + 1)};

        this->_color = {r, g, b, 255};
    }

    void Blob::decrease(float const percentage) {
        this->_radius = this->_radius * (1 - percentage);
    }

    void Blob::render() const {
        auto *drawList{ImGui::GetWindowDrawList()};
        drawList->AddCircleFilled(this->getCoords(), _radius, IM_COL32(_color.x, _color.y, _color.z, 255));
    }
}
