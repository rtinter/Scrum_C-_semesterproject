#pragma once

#include <Dashboard.hpp>
#include <Header.hpp>
#include <Scene.hpp>
#include <memory>

namespace scene {
    /**
     * @brief A scene representing the dashboard of the application.
     */
    class DashboardScene : public Scene {
        std::unique_ptr<views::Header> _header;  // Unique pointer to the header view
        std::unique_ptr<views::Dashboard> _dashboard;  // Unique pointer to the dashboard view

    public:
        /**
         * @brief Constructor: Initializes the DashboardScene with header and dashboard.
         */
        DashboardScene();

        /**
         * @brief Renders the dashboard scene, including the main header and dashboard with its Tiles.
         */
        void render() override;

        /**
         * @brief Gets the name of the scene.
         * @return The name of the Dashboard as a string.
         */
        std::string getName() const override;
    };
}
