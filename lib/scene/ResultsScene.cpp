
#include "ResultsScene.h"

namespace scene {

    ResultsScene::ResultsScene() : _header("Meine Werte", "Home", [](){
        //linking to Home/Dashboard site has to be added here
        //SceneManager::getInstance().switchTo(std::make_unique<PLACEHOLDER>());
    }){

    }


    void ResultsScene::render() {
        _header.render();
    }

    std::string ResultsScene::getName() const {
        return "ResultsScene";
    }
} // scene