//
// Created by jo on 5/30/24.
//

#ifndef ATHENA_TESTSCENE_HPP
#define ATHENA_TESTSCENE_HPP


#include "Scene.hpp"
#include <iostream>


class DashboardScene : public Scene {
    void render(sf::RenderWindow &window) const override { std::cout << "Render" << std::endl;}
    void update() const override { std::cout << "Update" << std::endl;}
};

template<typename T>
class GameScene : public Scene {
    T *_game;
    sf::RenderWindow &_window;
public:
    GameScene(sf::RenderWindow &window) : _window{window}{
        _game = new T();
        _game->start(_window);
    }
    void render(sf::RenderWindow &window) const override {
        _game->render(window);
    }
    void update() const override { std::cout << "Game Update" << std::endl;}
};


#endif //ATHENA_TESTSCENE_HPP
