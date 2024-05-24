//
// Created by jo on 5/24/24.
//

#ifndef ATHENA_SCENEMANAGER_HPP
#define ATHENA_SCENEMANAGER_HPP

#include "SceneContainer.hpp"

#include "memory"

namespace manager {
    class SceneManager {
    public:
        void handleEvents(sf::RenderWindow &window);
        void render(sf::RenderWindow &window);
        void update();
        static SceneManager getInstance();

    private:
        SceneManager();
        static void switchScene(std::unique_ptr<scene::SceneContainer> scene);

        static std::unique_ptr<scene::SceneContainer> _currentScene;
        static SceneManager _instance;
    };
}

#endif //ATHENA_SCENEMANAGER_HPP
