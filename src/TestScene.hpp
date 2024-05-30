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
public:
    GameScene() {
        _game = new T();
        _game->start();
    }
    void render(sf::RenderWindow &window) const override {
        _game->render();
    }
    void update() const override { std::cout << "Game Update" << std::endl;}
};


#endif //ATHENA_TESTSCENE_HPP
