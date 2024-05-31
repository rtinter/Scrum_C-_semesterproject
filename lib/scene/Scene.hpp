#ifndef ATHENA_SCENE_HPP
#define ATHENA_SCENE_HPP

#include <memory>
#include "imgui.h"
#include "SFML/Graphics.hpp"

class Scene {
public:
    virtual ~Scene() = default;
    virtual void render() const = 0;
};

#endif //ATHENA_SCENE_HPP
