#include "DashboardScene.hpp"
#include "ResultsScene.h"
#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "Reaction.hpp"
#include "ColorMatch.hpp"
#include "../games/matrix/MatrixGame.hpp"

using Tile = ui_elements::Tile;

scene::DashboardScene::DashboardScene() {

    _header = std::make_unique<views::Header>("Home", "Meine Werte", []() {
        //linking to user result site
        SceneManager::getInstance().switchTo(std::make_unique<ResultsScene>());
    });

    _dashboard = std::make_unique<views::Dashboard>();

    // initialize Categories
    std::vector<UniqueTile> kCategory1Tiles = {};
    std::vector<UniqueTile> kCategory2Tiles = {};


    // CREATE Reaktionsspiel in Category 1
    kCategory1Tiles.push_back(
            std::make_unique<Tile>(
                    "Pictogram1",
                    "Reaktionsspiel",
                    "Beschreibung1",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<reaction::Reaction>>()
                        );
                    }
            )
    );

    // CREATE Color Match in Category 1
    kCategory1Tiles.push_back(
            std::make_unique<Tile>(
                    "Pictogram2",
                    "Farbe & Text",
                    "Beschreibung2",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::ColorMatch>>());
                    }
            )
    );

    // CREATE Dummy in Category 2
    kCategory2Tiles.push_back(
            std::make_unique<Tile>(
                    "PictogramMatrix",
                    "Matrix",
                    "Matrix Beschreibung",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::MatrixGame>>());
                    }
            )
    );

    _dashboard->addTilesToCategory("Kategorie 1", kCategory1Tiles);
    _dashboard->addTilesToCategory("Kategorie 2", kCategory2Tiles);
}

void scene::DashboardScene::render() {
    // Header muss vor dem Dashboard rendern, da es die Größe für das Dashboard setzt
    if (_header)
        _header->render();
    if (_dashboard)
        _dashboard->render();
}

std::string scene::DashboardScene::getName() const {
    return "DashboardScene";
}
