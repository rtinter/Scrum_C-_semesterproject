
#ifndef ATHENA_RESULTSSCENE_H
#define ATHENA_RESULTSSCENE_H

#include "Scene.hpp"
#include "Header.hpp"
#include <string>

namespace scene {

    class ResultsScene : public Scene {

        views::Header _header;


    public:
        ResultsScene();

        void render() override;

        std::string getName() const override;
    };

} // scene

#endif //ATHENA_RESULTSSCENE_H
