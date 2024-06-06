#pragma once
#include "Scene.hpp"
#include "Header.hpp"
#include "Dashboard.hpp"
#include "GameScene.hpp"

class DashboardScene : public Scene {
    views::Header header;
    views::Dashboard dashboard;

public:
    DashboardScene();

    void render() override;
    std::string getName() const override;
};
