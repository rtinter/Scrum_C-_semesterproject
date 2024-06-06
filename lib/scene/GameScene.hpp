#pragma once
#include "Scene.hpp"
#include "Header.hpp"
#include "Reaction.hpp"

class GameScene : public Scene {
    views::Header header;
    games::Reaction reactionGame;

public:
    GameScene();

    void render() override;
};
