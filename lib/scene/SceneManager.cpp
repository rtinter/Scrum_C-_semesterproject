#include "SceneManager.hpp"

#include "DashboardScene.hpp"

namespace scene {
    // Get the singleton instance of the SceneManager
    SceneManager &SceneManager::getInstance() {
        static SceneManager instance;
        return instance;
    }

    void SceneManager::switchTo(std::unique_ptr<Scene> scene) {
        logger::Logger &logger{logger::Logger::getInstance()};
        std::stringstream ss;
        if (_currentScene != nullptr) {
            ss << "Deleting old Scene: " << _currentScene->getName();
            logger << (ss.str());
            ss.str("");
        }
        // move the old scene to the placeholder which gets deleted next frame
        _toBeDestroyedScene = std::move(_currentScene);
        // set the new scene
        _currentScene = std::move(scene);
        ss << "Switching Scene to: " << _currentScene->getName();
        logger << (ss.str());
    }

    // Render the current scene
    void SceneManager::render() {
        // if there is a scene to be destroyed, destroy it
        if (_toBeDestroyedScene) {
            _toBeDestroyedScene.reset();
        }
        // render the current scene
        if (_currentScene) {
            _currentScene->render();
        }
    }

    // has to be called after initialization of SceneManager
    void SceneManager::addDefaultScenes() {
        switchTo(std::make_unique<DashboardScene>());
    }
} // scene
