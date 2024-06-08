#include <iostream>
#include "SceneManager.hpp"

#include "DashboardScene.hpp"

// Get the singleton instance of the SceneManager
scene::SceneManager &scene::SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void scene::SceneManager::switchTo(std::unique_ptr<Scene> scene) {
    // move the old scene to the placeholder which gets deleted next frame
    _toBeDestroyedScene = std::move(_currentScene);
    // set the new scene
    _currentScene = std::move(scene);
}

// Render the current scene
void scene::SceneManager::render() {
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
void scene::SceneManager::addDefaultScenes() {
    switchTo(std::make_unique<DashboardScene>());
}
