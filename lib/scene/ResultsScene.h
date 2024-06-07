
#ifndef ATHENA_RESULTSSCENE_H
#define ATHENA_RESULTSSCENE_H

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

#endif //ATHENA_RESULTSSCENE_H
