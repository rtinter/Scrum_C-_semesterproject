#include "DashboardScene.hpp"
#include "ResultsScene.h"
#include "SceneManager.hpp"
#include "GameScene.hpp"
#include "Reaction.hpp"
#include "LetterSalad.hpp"
#include "ColorMatch.hpp"
#include "Sequence.hpp"
#include "AimTrainer.hpp"
#include "Remembering.hpp"
#include "TypeRacer.hpp"
#include "MatrixGame.hpp"

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
                    "Pictogram3",
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
                    "Pictogram3",
                    "Type Racer",
                    "Schnelles Tippen",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<typeracer::TypeRacer>>()
                        );
                    }
            )
    );

    accuracyCategory.push_back(
            std::make_unique<Tile>(
                    "Pictogram X",
                    "Sequence",
                    "Merke dir die Reihenfolge!",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<sequence::Sequence>>()
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

    problemSolvingCategory.push_back(
            std::make_unique<Tile>(
                    "",
                    "Matrix",
                    "Finde die gedrehte\nbzw. gespiegelte Matrix",
                    []() {
                        SceneManager::getInstance().switchTo(
                                std::make_unique<GameScene<game::MatrixGame>>()
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

    /* Durch die unordered_map und die fehlende rbegin()-Funktion wird die Reihenfolge der Kategorien
     * hier festgelegt.
    */
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
