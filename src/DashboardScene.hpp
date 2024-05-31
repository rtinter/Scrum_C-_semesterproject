#pragma once
#include "Scene.hpp"
#include "Header.hpp"
#include "Dashboard.hpp"

class DashboardScene : public Scene {
    Header header;
    views::Dashboard dashboard;

public:
    DashboardScene();

    void render() override;
};
