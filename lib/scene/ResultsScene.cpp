#include "ResultsScene.hpp"

#include <map>
#include <string>
#include <vector>

#include "CsvParser.hpp"
#include "CsvStorage.hpp"
#include "DashboardScene.hpp"
#include "GameIDs.hpp"
#include "SceneManager.hpp"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [] {
        SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
    }) {
        loadSessionData();
        displayResults();
    }

    /**
    * Loads session data from CSV files and processes it.
    * - Reads "game_session.csv" and "game_runthroughs.csv".
    * - Skips header rows.
    * - Converts start and end times to duration.
    * - Populates _sessionsMap with the session data.
    * - Prints the processed data for debugging.
    */
    void ResultsScene::loadSessionData() {
        // load csv data
        abstract_game::CsvStorage storage;
        csv::CsvParser gameSessionParser("game_session.csv");
        auto gameSessionData{gameSessionParser.parse()};

        csv::CsvParser gameRunThroughParser("game_runthroughs.csv");
        auto gameRunThroughData{gameRunThroughParser.parse()};

        if (gameSessionData.empty() || gameRunThroughData.empty()) {
            return;
        }

        // Skip column names
        if (!gameSessionData.empty()) {
            gameSessionData.erase(gameSessionData.begin());  // first entry: column names
        }

        if (!gameRunThroughData.empty()) {
            gameRunThroughData.erase(gameRunThroughData.begin());  // first entry: column names
        }

        // process data and fill data structure
        for (std::vector<std::string> const &row: gameSessionData) {
            if (!row.empty()) {
                int const gameID{std::stoi(row[0])};
                std::string sessionUID{row[1]};

                // Calculate number of runthroughs and mean result for entire session
                std::string resultUnit;
                int nRunthroughs{0};
                double resultSum{0.0};
                for (std::vector<std::string> const &runthrough: gameRunThroughData) {
                    if (!runthrough.empty()) {
                        if (sessionUID == runthrough[1]) {
                            nRunthroughs++;
                            resultSum += std::stod(runthrough[2]);
                            resultUnit = runthrough[3];
                        }
                    }
                }

                // Only create a new row if there are runthrough data for this session
                if (nRunthroughs > 0) {
                    std::string const startTimeStr{row[3]};
                    std::string const endTimeStr{row[4]};
                    std::string const durationStr{row[5]};

                    time_t const converted{stringToTimeT(startTimeStr)};
                    std::string const dateString{abstract_game::CsvStorage::getDateString(converted)};

                    // Convert start and end time to time_t
                    std::time_t const startTime{stringToTimeT(startTimeStr)};
                    std::time_t const endTime{stringToTimeT(endTimeStr)};

                    // Calculate duration in seconds
                    auto const duration{std::chrono::seconds(endTime - startTime)};

                    // Calculate mean result
                    double const meanResult{resultSum / nRunthroughs};

                    // Create string with mean result and unit
                    std::ostringstream streamObj;
                    streamObj << std::fixed << std::setprecision(2) << meanResult;
                    std::string const strMeanResult{streamObj.str()};
                    std::string combinedResult{strMeanResult};
                    combinedResult.append(" ").append(resultUnit);

                    // Create row with data
                    std::vector const sessionData{
                            dateString,
                            std::to_string(duration.count()) + " s",
                            std::to_string(nRunthroughs),
                            combinedResult
                    };
                    _sessionsMap[gameID].emplace_back(sessionUID, sessionData);
                }
            }
        }
    }

    /**
    * Displays the results by populating game tables with session data.
    * - Creates header line for tables.
    * - Maps session data to game tables.
    * - Adds game tables to the _results object for rendering.
    */
    void ResultsScene::displayResults() {

        std::vector<std::string> const stringvectorHeaderline{"Datum", "Dauer", "Versuche",
                                                        "Durchschnittliches Ergebnis"};
        std::map<int, ui_elements::StatisticsGameTable> gameTables;

        // add data to gameTables
        for (auto const &[fst, snd]: _sessionsMap) {
            std::string getGameName{abstract_game::getGameName(static_cast<abstract_game::GameID>(fst))};
            std::map<int, std::vector<std::string>> gameDataMap;
            gameDataMap[0] = stringvectorHeaderline;

            int rowIndex{1};
            for (const auto &[first, second]: snd) {
                std::vector const row{second};
                gameDataMap[rowIndex++] = row;
            }

            gameTables.emplace(fst, ui_elements::StatisticsGameTable(gameDataMap));
            _results.addGameTableContainer(ui_elements::TableContainer(getGameName, gameTables.at(fst)));
        }
    }

    void ResultsScene::render() {
        _header.render();
        _results.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }

    std::time_t ResultsScene::stringToTimeT(std::string const &timeStr) {
        return std::stoll(timeStr);
    }
} // scene
