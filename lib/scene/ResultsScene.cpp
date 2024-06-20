#include <iostream>
#include "ResultsScene.h"
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

    void ResultsScene::loadSessionData() {
        // Laden der CSV-Daten
        csv::CsvParser gameSessionParser("game_session.csv");
        auto gameSessionData = gameSessionParser.parse();

        csv::CsvParser gameRunThroughParser("game_runthroughs.csv");
        auto gameRunThroughData = gameRunThroughParser.parse();

        // Kopfzeilen überspringen
        if (!gameSessionData.empty()) {
            gameSessionData.erase(gameSessionData.begin());  // Erster Eintrag ist die Kopfzeile
        }

        if (!gameRunThroughData.empty()) {
            gameRunThroughData.erase(gameRunThroughData.begin());  // Erster Eintrag ist die Kopfzeile
        }

        // Verarbeiten der Daten und Befüllen der Datenstruktur
        for (const auto &row : gameSessionData) {
            if (row.size() >= 7) {
                int gameID = std::stoi(row[0]);
                std::string sessionUID = row[1];
                std::string startTime = row[3];
                std::string endTime = row[4];
                std::string duration = row[5];

                _sessionsMap[gameID].push_back({sessionUID, {startTime, endTime, duration}});
            }
        }

        for (const auto &row : gameRunThroughData) {
            if (row.size() >= 4) {
                std::string sessionUID = row[1];
                std::string result = row[2];
                std::string resultUnit = row[3];

                for (auto &pair : _sessionsMap) {
                    for (auto &session : pair.second) {
                        if (session.first == sessionUID) {
                            session.second.push_back(result + " " + resultUnit);
                        }
                    }
                }
            }
        }
    }

    void ResultsScene::displayResults() {
        std::vector<std::string> stringvectorHeaderline{"Datum", "Länge", "Sessions", "Werte"};
        std::map<int, ui_elements::StatisticsGameTable> gameTables;

        // Daten in die Tabelle einfügen
        for (const auto &pair : _sessionsMap) {
            std::string getGameName = abstract_game::getGameName(static_cast<abstract_game::GameID>(pair.first));
            std::map<int, std::vector<std::string>> gameDataMap;
            gameDataMap[0] = stringvectorHeaderline;

            int rowIndex = 1;
            for (const auto &session : pair.second) {
                std::vector<std::string> row = session.second;
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