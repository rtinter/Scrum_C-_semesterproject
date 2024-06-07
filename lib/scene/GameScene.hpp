#pragma once

#include "Header.hpp"
#include "Scene.hpp"
#include <string>
#include <memory>
#include "Reaction.hpp"

template<typename T>
class GameScene : public Scene {
    views::Header _header;
    std::unique_ptr<T> _game;
public:
    GameScene();
    void render() override;
    std::string getName() const override;
};

// Implementation of the GameScene template methods
template<typename T>
GameScene<T>::GameScene()
        : _header("Placeholder", "Zurück", []() {
    SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
}), _game{std::make_unique<T>()} {
}

template<typename T>
void GameScene<T>::render() {
    _game->start();
    _header.render();
}

template<typename T>
std::string GameScene<T>::getName() const {
    return "GameScene"; // Can be made more dynamic based on T
}

// Explicit instantiation of GameScene for games::Reaction
template class GameScene<games::Reaction>;

