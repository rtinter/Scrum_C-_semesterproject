//
// Created by jo on 5/23/24.
//


#ifndef ATHENA_SCENECONTAINER_HPP
#define ATHENA_SCENECONTAINER_HPP

#include <SFML/Graphics.hpp>

namespace scene {
    class SceneContainer {
    public:
        SceneContainer() = default;
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void handleEvents(sf::Event evt) = 0;
    private:
    };
#endif //ATHENA_SCENECONTAINER_HPP
}
