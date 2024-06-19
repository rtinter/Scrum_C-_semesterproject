#include "MatrixGame.hpp"
#include "Window.hpp"
#include "InfoBox.hpp"
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "RandomPicker.hpp"
#include "Centered.hpp"

namespace game {

    MatrixGame::MatrixGame() : Game(abstract_game::GameID::MATRIX) {
        _gameName = "Matrix";
        _gameDescription =
                "Das Spiel 'Matrix' trainiert das räumliche Vorstellungsvermögen";
        _gameRules = "Finde in der unteren Zeile die gedrehte/gespiegelte Version der oberen Matrix";
        _gameControls = "Linke Maustaste: Klicke auf die richtige Matrix in der unteren Zeile";
        _nColoredCellsMax = _mainMatrix.getSize() * _mainMatrix.getSize() / 2;
        _nColoredCellsMin = _mainMatrix.getSize();
    }

    void MatrixGame::render() {
        ui_elements::InfoBox(_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                             [this] {
                                 start();
                             }).render();

        ui_elements::InfoBox(_gameID, _showEndBox, "Endbox", _endBoxTitle, _endBoxText, [this] {
            start();
        }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    void MatrixGame::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, commons::Colors::BLACK);
        ui_elements::Window("Matrix Game").render([this] {
            _timer.render();
            _mainMatrix.renderBig(); // TODO: Positioning
            ImGui::SameLine();
            ui_elements::Centered(true, false, [this] {
                ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::BRIGHT_GREEN);
                ImGui::PushFont(commons::Fonts::_matrixFontBig);
                //ImGui::Text("ROTierT?");
                ImGui::Text("GesPiEgelT?");
                ImGui::PopStyleColor(); // pop ImGuiCol_Text
                ImGui::PopFont();
                for (Matrix matrix: _allRotatedVersions) {
                    matrix.renderSmall();
                    ImGui::NewLine();
                    ImGui::NewLine();

                }
            });
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                checkForCorrectClick();
            }

            if (_timer.isExpiredNow()) {
                stop();
            }
        });
        ImGui::PopStyleColor(); // pop ImGuiCol_WindowBg
    }

    void MatrixGame::stop() {
        _endBoxText =
                "Richtige: " + std::to_string(_nCorrectClicksInTotal) + "\nLängster Streak: " +
                std::to_string(_longestStreak);
        _isGameRunning = false;
        _showEndBox = true;
        _endBoxTitle = "Zeit abgelaufen!";
    }

    void MatrixGame::start() {
        reset();
        _isGameRunning = true;
        _showEndBox = false;
        _timer.start();
    }

    void MatrixGame::reset() {
        int nColoredCells{commons::RandomPicker::randomInt(_nColoredCellsMin, _nColoredCellsMax)};
        _mainMatrix.init(nColoredCells);
        _matricesToChooseFrom[0].init(nColoredCells); // TODO: loop doesnt work
        _matricesToChooseFrom[1].init(nColoredCells);
        _matricesToChooseFrom[2].init(nColoredCells);
        _allMirroredVersions = _mainMatrix.getAllMirroredVersions();
        _allRotatedVersions = _mainMatrix.getAllRotatedVersions();
    }

    void MatrixGame::updateStatistics() {

    }

    void MatrixGame::checkForCorrectClick() {
        for (int i{0}; i < 3; i++) {
            if (_matricesToChooseFrom[i]._isClicked) {
                std::cout << "Click";
                reset();
            }

        }

    }
} // game