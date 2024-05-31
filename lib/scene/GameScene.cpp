#include "GameScene.hpp"
#include "SceneManager.hpp"

GameScene::GameScene() : header("Game X", "Zurück", []() {
    SceneManager::getInstance().switchTo("DashboardScene");
}) {}

void GameScene::render() {
    header.render();
    reactionGame.start();
}
