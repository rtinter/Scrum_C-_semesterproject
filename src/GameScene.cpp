#include "GameScene.hpp"
#include "SceneManager.hpp"

template<typename T>
GameScene<T>::GameScene() : header("Game X", "Zurück", [](){
    SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
}) {}

template<typename T>
void GameScene<T>::render() {
    header.render();
    game->start();
}
