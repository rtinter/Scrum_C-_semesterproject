#include "DashboardScene.hpp"
#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "Reaction.hpp"
#include "ColorMatch.hpp"

scene::DashboardScene::DashboardScene() : _header("Home", "Meine Statistik", []() {
    //Add the linking to statistic site here
    // SceneManager::getInstance().switchTo(std::make_unique<PLACEHOLDER>());
}) {
    // Define tiles for the _dashboard
    std::vector<ui_elements::Tile> kCategory1Tiles = {
            ui_elements::Tile("Pictogram1", "Reaktionsspiel", "Beschreibung1", []() {
                SceneManager::getInstance().switchTo(std::make_unique<GameScene<games::Reaction>>());
            }),
            ui_elements::Tile("Pictogram2", "Farb-Wort-Spiel", "Beschreibung2", []() {
                SceneManager::getInstance().switchTo(std::make_unique<GameScene<games::ColorMatch>>());
            }),
    };

    std::vector<ui_elements::Tile> kCategory2Tiles = {
            ui_elements::Tile("Pictogram3", "Spielname3", "Beschreibung3", []() {}),
    };

    _dashboard.addTilesToCategory("Kategorie 1", kCategory1Tiles);
    _dashboard.addTilesToCategory("Kategorie 2", kCategory2Tiles);
}

void scene::DashboardScene::render() {
    _header.render();
    _dashboard.render();
}

std::string scene::DashboardScene::getName() const {
    return "DashboardScene";
}

