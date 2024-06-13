
#include "ResultsScene.h"
#include "DashboardScene.hpp"
#include "SceneManager.hpp"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
    }){
        //Testdaten -> Hier Spieldaten einbinden!
        std::map<int, std::vector<std::string>> map;
        std::vector<std::string> stringvector {"Test", "Daten", "Für", "Tabelle"};
        std::vector<std::string> stringvectordata {"Heute", "Tom", "300 pkt", "win"};
        map[1] = stringvector;
        map[2] = stringvectordata;
        ui_elements::StatisticsGameTable coolTable{map};
        _results.addGameTableContainer(ui_elements::TableContainer("hallo", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo1", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo3", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo4", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo5", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo6", coolTable));

    }


    void ResultsScene::render() {
        _header.render();
        _results.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene