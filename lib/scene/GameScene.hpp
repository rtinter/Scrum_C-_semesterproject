#pragma once

#include "Header.hpp"
#include "Scene.hpp"
#include <string>
#include <memory>
#include "Reaction.hpp"
#include "optional"
#include "GameSessionManager.hpp"
#include "ColorMatch.hpp"

namespace scene {
template<typename T>
class GameScene : public Scene {
  std::unique_ptr<views::Header> _header;
  std::unique_ptr<T> _game;
 public:
  GameScene();

        void render() override;

        std::string getName() const override;
    };

// Implementation of the GameScene template methods
template<typename T>
GameScene<T>::GameScene() : _game{std::make_unique<T>()} {
    // Header initialisieren, nachdem _game initialisiert wurde
    _header = std::make_unique<views::Header>(_game->getName(), "Zurück", []() {
        abstract_game::GameSessionManager::getInstance().endSession(); // End the session when going back
      SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
    });
}

template<typename T>
void GameScene<T>::render() {
    // Header muss vor dem Game rendern, da es die Größe für das Game setzt
    if (_header) {
        _header->render();
    }
    if (_game) {
        _game->render();
    }
}

    template<typename T>
    std::string GameScene<T>::getName() const {
        return _game->getName();
    }

// Explicit instantiation of GameScene for games::Reaction
template
class GameScene<reaction::Reaction>;

    template
    class GameScene<games::ColorMatch>;
}
