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
    std::vector<UniqueTile> reactionCategory = {};
    std::vector<UniqueTile> accuracyCategory = {};
    std::vector<UniqueTile> problemSolvingCategory = {};

    // Kategorie: Reaktion
    reactionCategory.push_back(
            std::make_unique<Tile>(
                    "",
                    "Reaktionsspiel",
                    "Reaktionsspiel Beschreibung",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<reaction::Reaction> >()
                        );
                    }
            )
    );

    reactionCategory.push_back(
            std::make_unique<Tile>(
                    "",
                    "Farbe & Text",
                    "Farbe & Text Beschreibung",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::ColorMatch> >());
                    }
            )
    );

    reactionCategory.push_back(
            std::make_unique<Tile>(
                    "",
                    "Aim Trainer",
                    "Aim Trainer Beschreibung",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::AimTrainer>>());
                    }
            )
    );

    // Kategorie: Genauigkeit
    accuracyCategory.push_back(
            std::make_unique<Tile>(
                    "",
                    "Type Racer",
                    "Schnelles Tippen",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<typeracer::TypeRacer>>()
                        );
                    }
            )
    );

    // Kategorie: Problemlösung
    problemSolvingCategory.push_back(
            std::make_unique<Tile>(
                    "",
                    "Buchstabensalat",
                    "Finde alle Wörter in vorgegebener Zeit",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<game::LetterSalad>>()
                        );
                    }
            )
    );

    /* Durch die unordered_map und die fehlende rbegin()-Funktion wird die Reihenfolge der Kategorien
     * hier festgelegt.
    */
    _dashboard->addTilesToCategory("Problemlösung", problemSolvingCategory);
    _dashboard->addTilesToCategory("Genauigkeit", accuracyCategory);
    _dashboard->addTilesToCategory("Reaktion", reactionCategory);
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
