#include "SceneManager.hpp"

// Get the singleton instance of the SceneManager
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

// Add a new scene to the scene manager
void SceneManager::addScene(const std::string& name, std::unique_ptr<Scene> scene) {
    _scenes[name] = std::move(scene);
}

// Switch to a different scene by name
void SceneManager::switchTo(const std::string& name) {
    auto it = _scenes.find(name);
    if (it != _scenes.end()) {
        _currentScene = it->second.get();
    }
}

// Render the current scene
void SceneManager::render() {
    if (_currentScene) {
        _currentScene->render();
    }
}
