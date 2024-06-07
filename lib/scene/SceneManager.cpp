#include "SceneManager.hpp"
#include "DashboardScene.hpp"


// Get the singleton instance of the SceneManager
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::switchTo(std::unique_ptr<Scene> scene) {
    if(_currentScene)
        _currentScene.release();

    _currentScene = std::move(scene);
}

// Render the current scene
void SceneManager::render() {
    if (_currentScene) {
        _currentScene->render();
    }
}

// has to be called after initialization of SceneManager
void SceneManager::addDefaultScenes() {
    switchTo(std::make_unique<DashboardScene>());
}

