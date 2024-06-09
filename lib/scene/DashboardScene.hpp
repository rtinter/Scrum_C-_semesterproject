#pragma once

#include <Dashboard.hpp>
#include <Header.hpp>
#include <Scene.hpp>
#include <memory>

namespace scene {
    class DashboardScene : public Scene {
        std::unique_ptr<views::Header> _header;
        std::unique_ptr<views::Dashboard> _dashboard;

    public:
        DashboardScene();

        void render() override;

        std::string getName() const override;
    };
}
