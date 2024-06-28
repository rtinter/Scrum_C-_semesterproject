
#ifndef ATHENA_RESULTSSCENE_HPP
#define ATHENA_RESULTSSCENE_HPP

#include "Scene.hpp"
#include "Header.hpp"
#include "Results.hpp"
#include <string>
#include <CsvStorage.hpp>

namespace scene {

    /*********************************
    * The ResultsScene class handles the loading, processing,
    * and displaying of session results.
    ***********************************/
    class ResultsScene : public Scene {

        views::Header _header;
        views::Results _results;
        std::map<int, std::vector<std::pair<std::string, std::vector<std::string>>>> _sessionsMap;

        void loadSessionData();
        void displayResults();
        std::time_t stringToTimeT(std::string const &timeStr) {
            return std::stoll(timeStr);
        }

    public:
        ResultsScene();

        void render() override;

        std::string getName() const override;
    };

} // scene

#endif //ATHENA_RESULTSSCENE_HPP
