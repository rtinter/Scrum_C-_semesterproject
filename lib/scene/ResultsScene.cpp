#include <iostream>
#include "ResultsScene.h"
#include "DashboardScene.hpp"
#include "SceneManager.hpp"
#include "CsvParser.hpp"
#include "GameIDs.hpp"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
    }){
        std::vector<std::string> stringvectorHeaderline {"Datum", "Länge", "Sessions", "Werte"};
        std::map<int, std::vector<std::string>> dataMap;
        std::vector<std::string> dataVector;
        ui_elements::StatisticsGameTable dataTable{dataMap};

        csv::CsvParser csvParser("game_session.csv");
        auto data = csvParser.parse();

        for (auto const &row : data) {
            std::cout << "Row: " << std::endl;
            for (auto const &field : row) {
                // reihe per Spiel abspeichern und dann in die Tabelle einfügen
                // GameID sollte gleich dem 0ten Feld sein
                if (field == abstract_game::GameID) {

                }

            }
            dataMap[dataMap.size()] = dataVector;
        }



        dataVector = {"Heute", "Tom", "300 pkt", "win"};
        dataMap[0] = stringvectorHeaderline;
        dataMap[1] = dataVector;
        dataTable = ui_elements::StatisticsGameTable{dataMap};
        _results.addGameTableContainer(ui_elements::TableContainer("Reaktion", dataTable));


    }

    void ResultsScene::render() {
        _header.render();
        _results.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene