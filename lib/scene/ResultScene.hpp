#pragma once
#include "Scene.hpp"
#include "Header.hpp"
#include "Results.h"
#include <string>

namespace scene {

    class ResultsScene : public Scene {
        views::Header _header;
        views::Results _results;


    public:
        ResultsScene();

        void render() override;

        std::string getName() const override;
    };

} // scene
