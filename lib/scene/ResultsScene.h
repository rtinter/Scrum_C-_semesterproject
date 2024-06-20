
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
        std::map<int, std::vector<std::pair<std::string, std::vector<std::string>>>> _sessionsMap;

        void loadSessionData();
        void displayResults();
        std::time_t stringToTimeT(const std::string &timeStr) {
            return std::stoll(timeStr);
        }

    public:
        ResultsScene();

        void render() override;

        std::string getName() const override;
    };

} // scene

#endif //ATHENA_RESULTSSCENE_H
