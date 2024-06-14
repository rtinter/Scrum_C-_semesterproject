#include "DashboardScene.hpp"
#include "ResultsScene.h"
#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "Reaction.hpp"
#include "LetterSalad.hpp"
#include "ColorMatch.hpp"
#include "AimTrainer.hpp"
#include "Remembering.hpp"
#include "TypeRacer.hpp"
#include "RowsOfNumbers.hpp"


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
    std::vector<UniqueTile> rememberCategory = {};
    std::vector<UniqueTile> logicalThinking = {};

    // Kategorie: Reaktion
    reactionCategory.push_back(
            std::make_unique<Tile>(
                    "Reaktionsspiel",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<reaction::Reaction> >()
                        );
                    }
            )
    );

    reactionCategory.push_back(
            std::make_unique<Tile>(
                    "Farbe & Text",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::ColorMatch> >());
                    }
            )
    );

    reactionCategory.push_back(
            std::make_unique<Tile>(
                    "Aim Trainer",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::AimTrainer>>());
                    }
            )
    );

    // Kategorie: Genauigkeit
    accuracyCategory.push_back(
            std::make_unique<Tile>(
                    "Type Racer",
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
                    "",
                    "Buchstabensalat",
                    "Finde alle Wörter\nin vorgegebener Zeit",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<game::LetterSalad>>()
                        );
                    }
            )
    );

    // Kategorie: Merkfähigkeit
    rememberCategory.push_back(
            std::make_unique<Tile>(
                    "",
                    "Fakten merken",
                    "Merke dir so möglichst\nviele Fakten",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<games::Remembering>>()
                        );
                    }
            )
    );

    // Kategorie: Logisches Denken
    logicalThinking.push_back(
            std::make_unique<Tile>(
                    "",
                    "Zahlenreihen",
                    "Finde die fehlende Zahl",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<game::RowsOfNumbers>>()
                        );
                    }
            )
    );


    /* Durch die unordered_map und die fehlende rbegin()-Funktion wird die Reihenfolge der Kategorien
     * hier festgelegt.
    */
    _dashboard->addTilesToCategory("Logisches Denken", logicalThinking);
    _dashboard->addTilesToCategory("Problemlösung", problemSolvingCategory);
    _dashboard->addTilesToCategory("Merkfähigkeit", rememberCategory);
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
