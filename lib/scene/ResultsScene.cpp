#include <iostream>
#include "ResultsScene.hpp"
#include "DashboardScene.hpp"
#include "SceneManager.hpp"
#include "CsvParser.hpp"
#include "GameIDs.hpp"
#include <map>
#include <vector>
#include <string>

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
    }) {
        loadSessionData();
        displayResults();
    }

    /*********************************
    * Loads session data from CSV files and processes it.
    * - Reads "game_session.csv" and "game_runthroughs.csv".
    * - Skips header rows.
    * - Converts start and end times to duration.
    * - Populates _sessionsMap with the session data.
    * - Prints the processed data for debugging.
    ***********************************/
    void ResultsScene::loadSessionData() {
        // Laden der CSV-Daten

        abstract_game::CsvStorage storage;
        csv::CsvParser gameSessionParser("game_session.csv");
        auto gameSessionData{gameSessionParser.parse()};

        csv::CsvParser gameRunThroughParser("game_runthroughs.csv");
        auto gameRunThroughData{gameRunThroughParser.parse()};

        if (gameSessionData.empty() || gameRunThroughData.empty()) {
            return;
        }

        // Kopfzeilen überspringen
        if (!gameSessionData.empty()) {
            gameSessionData.erase(gameSessionData.begin());  // Erster Eintrag ist die Kopfzeile
        }

        if (!gameRunThroughData.empty()) {
            gameRunThroughData.erase(gameRunThroughData.begin());  // Erster Eintrag ist die Kopfzeile
        }

        // Verarbeiten der Daten und Befüllen der Datenstruktur
        for (auto const &row : gameSessionData) {
            if (!row.empty()) {
                int gameID{std::stoi(row[0])};
                std::string sessionUID {row[1]};
                std::string startTimeStr {row[3]};
                std::string endTimeStr {row[4]};
                std::string durationStr{row[5]};

                time_t converted {stringToTimeT(startTimeStr)};
                std::string dateString {storage.getDateString(converted)};

                // Konvertiere Start- und Endzeit in time_t
                std::time_t startTime {stringToTimeT(startTimeStr)};
                std::time_t endTime {stringToTimeT(endTimeStr)};

                // Berechne die Dauer in Sekunden
                std::chrono::seconds duration {std::chrono::seconds(endTime - startTime)};

                // Erstelle die Datenzeile
                std::vector<std::string> sessionData {
                        dateString,
                        std::to_string(duration.count()) + " s",
                };

                _sessionsMap[gameID].push_back({sessionUID, sessionData});
            }
        }

        for (auto const &pair : _sessionsMap) {
            std::cout << "GameID: " << pair.first << " ";
            for (auto const &session : pair.second) {
                std::cout << "SessionUID: " << session.first << " ";
                for (auto const &value : session.second) {
                    std::cout << value << " ";
                }
            }
            std::cout << std::endl;
        }

        for (auto const &row : gameRunThroughData) {
                std::cout << "Row: ";
                std::cout << row.size() << " ";
                for (auto const &field : row) {
                    std::cout << field << " ";
                }
                std::cout << std::endl;

            if (!row.empty()) {
                std::string sessionUID {row[1]};
                std::string result {row[2]};
                std::string resultUnit {row[3]};

                int totalSessions {0};
                std::string totalSessionsString;

                // Skip this session if there is no result
                if (result.empty()) {
                    continue;
                }

                for (auto &pair : _sessionsMap) {
                    totalSessions += pair.second.size();
                    totalSessionsString = std::to_string(totalSessions);
                    for (auto &session : pair.second) {
                        std::cout << session.first << " " << sessionUID << std::endl;
                        if (session.first == sessionUID) {
                            std::cout << "Result " << result << " " << resultUnit << std::endl;
                            std::string combinedResult {result};
                            combinedResult.append(" ").append(resultUnit);
                            session.second.push_back(totalSessionsString);
                            session.second.push_back(combinedResult);
                        }
                    }
                }
            }
        }

        // Debug print of _sessionsMap content -> kept for logging and debugging purposes
        for (auto const &pair : _sessionsMap) {
            std::cout << "GameID: " << pair.first << " ";
            for (auto const &session : pair.second) {
                std::cout << "SessionUID: " << session.first << " ";
                for (auto const &value : session.second) {
                    std::cout << value << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    /*********************************
    * Displays the results by populating game tables with session data.
    * - Creates header line for tables.
    * - Maps session data to game tables.
    * - Adds game tables to the _results object for rendering.
    ***********************************/
    void ResultsScene::displayResults() {

        std::vector<std::string> stringvectorHeaderline{"Datum", "Dauer", "Anzahl der Sessions", "Ergebnis"};
        std::map<int, ui_elements::StatisticsGameTable> gameTables;

        // add data to gameTables
        for (auto const &pair : _sessionsMap) {
            std::string getGameName {abstract_game::getGameName(static_cast<abstract_game::GameID>(pair.first))};
            std::map<int, std::vector<std::string>> gameDataMap;
            gameDataMap[0] = stringvectorHeaderline;

            int rowIndex {1};
            for (auto const &session : pair.second) {
                std::cout << "Session: " << session.first << std::endl;

                std::vector<std::string> row {session.second};
                gameDataMap[rowIndex++] = row;
            }

            gameTables.emplace(pair.first, ui_elements::StatisticsGameTable(gameDataMap));
            _results.addGameTableContainer(ui_elements::TableContainer(getGameName, gameTables.at(pair.first)));
        }
    }

    void ResultsScene::render() {
        _header.render();
        _results.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene