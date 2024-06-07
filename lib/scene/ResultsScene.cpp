
#include "ResultsScene.h"
#include "StatisticsGameTable.hpp"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        //linking to Home/Dashboard site has to be added here
        //SceneManager::getInstance().switchTo(std::make_unique<PLACEHOLDER>());
    }){

        std::map<int, std::vector<std::string>> coolMap;
        ui_elements::StatisticsGameTable coolTable{coolMap};
        _results.addGameTableContainer(ui_elements::TableContainer("hall0", coolTable));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo1", coolTable));

    }


    void ResultsScene::render() {
        _header.render();
        _results.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene