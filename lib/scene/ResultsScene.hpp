#pragma once

#include <string>
#include <chrono>

#include "Header.hpp"
#include "Results.hpp"
#include "Scene.hpp"

namespace scene {
    /**
     * @brief A scene representing the results of a session.
     */
    class ResultsScene final : public Scene {
        views::Header _header;
        views::Results _results;
        std::map<int, std::vector<std::pair<std::string, std::vector<std::string> > > > _sessionsMap;

        void loadSessionData();

        void displayResults();

        static std::time_t stringToTimeT(std::string const &timeStr);

    public:
        ResultsScene();

        void render() override;

        std::string getName() const override;
    };
} // scene
