#include "SceneManager.hpp"
#include "DashboardScene.hpp"

// Get the singleton instance of the SceneManager
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::switchTo(std::unique_ptr<Scene> scene) {
    if(currentScene)
        currentScene.release();

    currentScene = std::move(scene);
}

// Render the current scene
void SceneManager::render() {
    if (currentScene) {
        currentScene->render();
    }
}

// has to be called after initialization of SceneManager
void SceneManager::addDefaultScenes() {
    switchTo(std::make_unique<DashboardScene>());
}