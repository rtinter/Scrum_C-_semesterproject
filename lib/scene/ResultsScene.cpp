
#include "ResultsScene.h"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        //linking to Home/Dashboard site has to be added here
        //SceneManager::getInstance().switchTo(std::make_unique<PLACEHOLDER>());
    }){

        _results.addGameTableContainer(ui_elements::TableContainer("hallo"));
        _results.addGameTableContainer(ui_elements::TableContainer("hallo1"));

    }


    void ResultsScene::render() {
        _header.render();
        _results.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene