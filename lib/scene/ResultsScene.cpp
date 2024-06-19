#include "ResultsScene.h"
#include "DashboardScene.hpp"
#include "SceneManager.hpp"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
    }){
        std::vector<std::string> stringvectorHeaderline {"Datum", "Länge", "Sessions", "Werte"};

        std::map<int, std::vector<std::string>> dataMap;
        std::vector<std::string> dataVector;
        ui_elements::StatisticsGameTable dataTable{dataMap};

        dataVector = {"Heute", "Tom", "300 pkt", "win"};
        dataMap[0] = stringvectorHeaderline;
        dataMap[1] = dataVector;
        dataTable = ui_elements::StatisticsGameTable{dataMap};
        _results.addGameTableContainer(ui_elements::TableContainer("Reaktion", dataTable));

        dataVector = {"Heute", "Tom", "300 pkt", "win"};
        dataMap[0] = stringvectorHeaderline;
        dataMap[1] = dataVector;
        dataTable = ui_elements::StatisticsGameTable{dataMap};
        _results.addGameTableContainer(ui_elements::TableContainer("Farbe & Text", dataTable));

        dataVector = {"Heute", "Tom", "300 pkt", "win"};
        dataMap[0] = stringvectorHeaderline;
        dataMap[1] = dataVector;
        dataTable = ui_elements::StatisticsGameTable{dataMap};
        _results.addGameTableContainer(ui_elements::TableContainer("Aim Trainer", dataTable));

        dataVector = {"", "Tom", "300 pkt", "win"};
        dataMap[0] = stringvectorHeaderline;
        dataMap[1] = dataVector;
        dataTable = ui_elements::StatisticsGameTable{dataMap};
        _results.addGameTableContainer(ui_elements::TableContainer("Type Racer", dataTable));

        dataVector = {"Heute", "Tom", "300 pkt", "win"};
        dataMap[0] = stringvectorHeaderline;
        dataMap[1] = dataVector;
        dataTable = ui_elements::StatisticsGameTable{dataMap};
        _results.addGameTableContainer(ui_elements::TableContainer("Sequence", dataTable));

        dataVector = {"Heute", "Tom", "300 pkt", "win"};
        dataMap[0] = stringvectorHeaderline;
        dataMap[1] = dataVector;
        dataTable = ui_elements::StatisticsGameTable{dataMap};
        _results.addGameTableContainer(ui_elements::TableContainer("Fakten merken", dataTable));
    }

    void ResultsScene::render() {
        _header.render();
        _results.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene