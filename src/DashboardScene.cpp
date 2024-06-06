#include "DashboardScene.hpp"
#include "SceneManager.hpp"

DashboardScene::DashboardScene() : header("Home", "Zurück", []() {
    SceneManager::getInstance().switchTo(std::make_unique<DashboardScene>());
}) {
    // Define tiles for the dashboard
    const std::vector<ui_elements::Tile> kCategory1Tiles = {
            ui_elements::Tile("Pictogram1", "Reaktionsspiel", "Beschreibung1", []() {
                SceneManager::getInstance().switchTo(std::make_unique<GameScene<reaction::Reaction>>());
            }),
            ui_elements::Tile("Pictogram2", "Spielname2", "Beschreibung2", []() {}),
    };
    const std::vector<ui_elements::Tile> kCategory2Tiles = {
            ui_elements::Tile("Pictogram3", "Spielname3", "Beschreibung3", []() {}),
    };
    dashboard.addTilesToCategory("Kategorie 1", kCategory1Tiles);
    dashboard.addTilesToCategory("Kategorie 2", kCategory2Tiles);
}

void DashboardScene::render() {
    header.render();
    dashboard.render();
}
