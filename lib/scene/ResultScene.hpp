#pragma once
#include "Scene.hpp"
#include "Header.hpp"
#include "Results.h"
#include <string>
#include "Session.hpp"

namespace scene {
    class ResultScene : public Scene {
        views::Header _header;
        views::Results _results;

        std::vector<Session> _sessions;

    public:
        ResultScene();

        void render() override;

        std::string getName() const override;
    };

} // scene
