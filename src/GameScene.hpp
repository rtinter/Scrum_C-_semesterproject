#pragma once
#include "Scene.hpp"
#include "Header.hpp"
#include "Reaction.hpp"

class GameScene : public Scene {
    Header header;
    reaction::Reaction reactionGame;

public:
    GameScene();

    void render() override;
};
