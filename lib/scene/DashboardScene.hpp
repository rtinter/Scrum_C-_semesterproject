#pragma once

#include <Dashboard.hpp>
#include <Header.hpp>
#include <Scene.hpp>


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
