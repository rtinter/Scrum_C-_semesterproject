#include "GameScene.hpp"
#include "SceneManager.hpp"
#include "DashboardScene.hpp"


template<typename T>
GameScene<T>::GameScene() : header("Game Title", "Back", []() {
    SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
}), _game{std::make_unique<T>()} {
}

template<typename T>
void GameScene<T>::render() {
    _game->start();   // Ensure T has a method named `start`
    header.render();  // Assuming `Header` has a method named `render`
}

template<typename T>
std::string GameScene<T>::getName() const {
    return "GameScene"; // Can be made more dynamic based on T
}