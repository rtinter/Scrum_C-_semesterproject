#include "SceneManager.hpp"
#include "DashboardScene.hpp"
#include "GameScene.hpp"
#include "Reaction.hpp"

// Get the singleton instance of the SceneManager
SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

// Add a new scene to the scene manager
// void SceneManager::addScene(std::unique_ptr<Scene> scene) {
//     std::string name = scene->getName();
//     scenes[name] = std::move(scene);
// }
//
// // Switch to a different scene by name
// void SceneManager::switchTo(const std::string& name) {
//     auto it = scenes.find(name);
//     if (it != scenes.end()) {
//         currentScene = it->second.get();
//     }
// }

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