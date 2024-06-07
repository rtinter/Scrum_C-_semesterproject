#pragma once

#include "Scene.hpp"
#include "Header.hpp"
#include "Dashboard.hpp"
#include <string>

namespace scene {
    class DashboardScene : public Scene {
        views::Header _header;
        views::Dashboard _dashboard;

    public:
        DashboardScene();

        void render() override;

        std::string getName() const override;
    };
}