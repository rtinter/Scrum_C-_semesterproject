#include "DashboardScene.hpp"
#include "ResultsScene.h"
#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "Reaction.hpp"
#include "ColorMatch.hpp"

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
            "Reaktionsspiel",
            []() {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<reaction::Reaction> >()
                );
            }
        )
    );

    // CREATE Color Match in Category 1
    kCategory1Tiles.push_back(
        std::make_unique<Tile>(
            "Farbe & Text",
            []() {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::ColorMatch> >());
            }
        )
    );

    _dashboard->addTilesToCategory("Spiele", kCategory1Tiles);
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
