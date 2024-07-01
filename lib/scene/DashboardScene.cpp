#include "DashboardScene.hpp"

#include "AimTrainer.hpp"
#include "Analogy.hpp"
#include "Calc.hpp"
#include "ColorMatch.hpp"
#include "Conclusions.hpp"
#include "GameScene.hpp"
#include "LetterSalad.hpp"
#include "MatrixGame.hpp"
#include "Memory.hpp"
#include "Reaction.hpp"
#include "Remembering.hpp"
#include "ResultsScene.hpp"
#include "RowsOfNumbers.hpp"
#include "RowsOfSymbols.hpp"
#include "SceneManager.hpp"
#include "SimonSays.hpp"
#include "TypeRacer.hpp"


using Tile = ui_elements::Tile;

scene::DashboardScene::DashboardScene() {
    _header = std::make_unique<views::Header>("Home", "Meine Werte", [] {
        // linking to user result site
        SceneManager::getInstance().switchTo(std::make_unique<ResultsScene>());
    });

    _dashboard = std::make_unique<views::Dashboard>();

    // initialize Categories
    std::vector<UniqueTile> reactionCategory{};
    std::vector<UniqueTile> accuracyCategory{};
    std::vector<UniqueTile> problemSolvingCategory{};
    std::vector<UniqueTile> rememberCategory{};
    std::vector<UniqueTile> logicalThinking{};

    // Kategorie: Reaktion
    reactionCategory.push_back(
        std::make_unique<Tile>(
            "",
            "Reaktionsspiel",
            "Klicke, sobald es grün wird!",
            commons::Colors::BLUE,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::Reaction> >()
                );
            }
        )
    );

    reactionCategory.push_back(
        std::make_unique<Tile>(
            "",
            "Farbe & Wort",
            "Welche Farbe passt zum Wort?\n"
            "Welches Wort passt zur Farbe?",
            commons::Colors::BLUE,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::ColorMatch> >());
            }
        )
    );

    reactionCategory.push_back(
        std::make_unique<Tile>(
            "",
            "Aim Trainer",
            "Triff die Ziele schnell",
            commons::Colors::BLUE,
            []() {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::AimTrainer> >());
            }
        )
    );

    reactionCategory.push_back(
        std::make_unique<Tile>(
            "\uF61F",
            "Symbolreihen",
            "Symbole erkennen und einordnen",
            commons::Colors::BLUE,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::RowsOfSymbols> >());
            }
        )
    );

    // Kategorie: Genauigkeit
    accuracyCategory.push_back(
        std::make_unique<Tile>(
            "",
            "Type Racer",
            "Schnelles Tippen",
            commons::Colors::ORANGE,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::TypeRacer> >()
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
            commons::Colors::GREEN,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::LetterSalad> >()
                );
            }
        )
    );

    problemSolvingCategory.push_back(
        std::make_unique<Tile>(
            "",
            "Matrix",
            "Finde die gedrehte\nbzw. gespiegelte Matrix",
            commons::Colors::GREEN,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::MatrixGame> >()
                );
            }
        )
    );

    // Kategorie: Merkfähigkeit
    rememberCategory.push_back(
        std::make_unique<Tile>(
            "",
            "Fakten merken",
            "Merke dir möglichst viele Fakten",
            commons::Colors::YELLOW,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::Remembering> >()
                );
            }
        )
    );
    rememberCategory.push_back(
        std::make_unique<Tile>(
            "",
            "Simon Says",
            "Merke dir die Reihenfolge!",
            commons::Colors::YELLOW,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::SimonSays> >()
                );
            }
        )
    );

    rememberCategory.push_back(
        std::make_unique<Tile>(
            "\uF5FD",
            "Memory",
            "Finde alle Paare",
            commons::Colors::YELLOW,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::Memory> >()
                );
            }
        )
    );

    // Kategorie: Logisches Denken
    logicalThinking.push_back(
        std::make_unique<Tile>(
            "1235?",
            "Zahlenreihen",
            "Finde die fehlende Zahl",
            commons::Colors::SEAFOAM,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::RowsOfNumbers> >()
                );
            }
        )
    );

    logicalThinking.push_back(
        std::make_unique<Tile>(
            "\uF1EC",
            "Schnelles Rechnen",
            "Löse Rechenaufgaben",
            commons::Colors::SEAFOAM,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::Calc> >()
                );
            }
        )
    );


    // Kategorie: Logisches Denken
    logicalThinking.push_back(
        std::make_unique<Tile>(
            "\uE13A",
            "Analogien",
            "Finde das passende Wort",
            commons::Colors::SEAFOAM,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::Analogy> >()
                );
            }
        )
    );

    logicalThinking.push_back(
        std::make_unique<Tile>(
            "",
            "Schlussfolgerungen",
            "Erschließe die logische Schlussfolgerung",
            commons::Colors::SEAFOAM,
            [] {
                SceneManager::getInstance().switchTo(
                    std::make_unique<GameScene<games::Conclusions> >()
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
