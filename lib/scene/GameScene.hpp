#pragma once

#include <memory>
#include <string>

#include "ColorMatch.hpp"
#include "GameSessionManager.hpp"
#include "Header.hpp"
#include "Reaction.hpp"
#include "Scene.hpp"

namespace scene {
    /**
    * @brief A template class for representing a game scene.
    * @tparam T The type (name) of the game.
    */
    template<typename T>
    class GameScene final : public Scene {
        std::unique_ptr<views::Header> _header;
        std::unique_ptr<T> _game;

    public:
        GameScene();

        void render() override;

        std::string getName() const override;
    };

    // Implementation of the GameScene template methods

    /**
     * @brief Constructor: Initializes the game and the header.
     * @tparam T The type (name) of the game eg. GameScene<games::Calc>.
     */
    template<typename T>
    GameScene<T>::GameScene() : _game{std::make_unique<T>()} {
        // Initialize the header after the game is initialized
        _header = std::make_unique<views::Header>(_game->getName(), "Zurück", []() {
            // End the session when going back
            abstract_game::GameSessionManager::endSession();
            SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
        });
    }

    /**
     * @brief Renders the game scene, including the header and the game.
     * @tparam T The type (name) of the game.
     */
    template<typename T>
    void GameScene<T>::render() {
        // Render the header before the game, as it sets the size for the game
        if (_header) {
            _header->render();
        }
        if (_game) {
            _game->render();
        }
    }

    /**
     * @brief Gets the name of the scene.
     * @tparam T The type (name) of the game.
     * @return The name of the game as a string.
     */
    template<typename T>
    std::string GameScene<T>::getName() const {
        return _game->getName();
    }

    // Explicit instantiation of GameScene for reaction::Reaction
    template
    class GameScene<games::Reaction>;

    // Explicit instantiation of GameScene for games::ColorMatch
    template
    class GameScene<games::ColorMatch>;
}
