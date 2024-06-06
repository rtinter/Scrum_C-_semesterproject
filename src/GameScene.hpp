#pragma once
#include "Scene.hpp"
#include "Header.hpp"
#include "Reaction.hpp"
#include "DashboardScene.hpp"

// T needs to be Type = Game
template<typename T>
class GameScene : public Scene {
    Header header;
    std::unique_ptr<T> game;

public:
    GameScene<T>();

    void render() override;
};

template class GameScene<reaction::Reaction>;