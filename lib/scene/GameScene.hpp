#pragma once

#include "Header.hpp"
#include "Scene.hpp"
#include <string>
#include <memory>
#include "Reaction.hpp"
#include "ColorText.hpp"
#include "optional"

namespace scene {
    template<typename T>
    class GameScene : public Scene {
        std::optional<views::Header> _header;
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
        _header.emplace(_game->getName(), "Zurück", []() {
            SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
        });
    }

    template<typename T>
    void GameScene<T>::render() {
        _game->start();
        _header->render();
    }

    template<typename T>
    std::string GameScene<T>::getName() const {
        return _game->getName();
    }

// Explicit instantiation of GameScene for games::Reaction
    template
    class GameScene<games::Reaction>;
    template
    class GameScene<games::ColorText>;
}