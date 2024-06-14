#include "DashboardScene.hpp"
#include "ResultsScene.h"
#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "Reaction.hpp"
#include "LetterSalad.hpp"
#include "ColorMatch.hpp"
#include "AimTrainer.hpp"
#include "../games/typeracer/TypeRacer.hpp"


using Tile = ui_elements::Tile;

scene::DashboardScene::DashboardScene() {

    _header = std::make_unique<views::Header>("Home", "Meine Werte", []() {
        // linking to user result site
        SceneManager::getInstance().switchTo(std::make_unique<ResultsScene>());
    });

    _dashboard = std::make_unique<views::Dashboard>();

    // initialize Categories
    std::vector<UniqueTile> kCategory1Tiles = {};
    std::vector<UniqueTile> kCategory2Tiles = {};
    std::vector<UniqueTile> kCategory3Tiles = {};


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

    // CREATE Dummy in Category 2
    kCategory1Tiles.push_back(
            std::make_unique<Tile>(
                    "Aim Trainer",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::AimTrainer>>());
                    }
            )
    );

    // CREATE Color Match in Category 1
    kCategory1Tiles.push_back(
            std::make_unique<Tile>(
                    "Type Racer",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<typeracer::TypeRacer>>()
                        );
                    }
            )
    );

    // CREATE LetterSalad in Category 3
    kCategory3Tiles.push_back(
            std::make_unique<Tile>(
                    "Pic",
                    "Buchstabensalat",
                    "Finde alle Wörter\nin vorgegebener Zeit",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<game::LetterSalad>>()
                        );
                    }
            )
    );

    _dashboard->addTilesToCategory("Kategorie 1", kCategory1Tiles);
    _dashboard->addTilesToCategory("Kategorie 2", kCategory2Tiles);
    _dashboard->addTilesToCategory("Kategorie 3", kCategory3Tiles);
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
