#pragma once
#include <map>
#include <memory>
#include <string>
#include "Scene.hpp"
#include "Logger.hpp"

namespace scene {
    /**
   * @brief Manages scenes within the application, including switching and rendering scenes.
   */
    class SceneManager {
        std::map<std::string, std::unique_ptr<Scene>> _scenes;
        std::unique_ptr<Scene> _currentScene;
        std::unique_ptr<Scene> _toBeDestroyedScene;

    public:
        /**
         * @brief Gets the singleton instance of the SceneManager.
         * @return Reference to the singleton instance.
         */
        static SceneManager &getInstance();

        /**
         * @brief Switches to a new scene.
         * @param scene Unique pointer to the new scene.
         */
        void switchTo(std::unique_ptr<Scene> scene);

        /**
         * @brief Adds default scenes to the SceneManager.
         */
        void addDefaultScenes();

        /**
         * @brief Renders the current scene.
         */
        void render();
    };
}
