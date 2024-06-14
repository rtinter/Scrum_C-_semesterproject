#include "MatrixGame.hpp"
#include "Window.hpp"
#include "InfoBox.hpp"
#include "Fonts.hpp"
#include "TextCentered.hpp"

namespace games {

    MatrixGame::MatrixGame() : Game(abstract_game::GameID::MATRIX) {
        _gameName = "Matrix";
        _gameDescription =
                "Das Spiel 'Matrix' trainiert das räumliche Vorstellungsvermögen";
        _gameRules = "Finde in der unteren Zeile die gedrehte/gespiegelte Version der oberen Matrix";
        _gameControls = "Linke Maustaste: Klicke auf die richtige Matrix in der unteren Zeile";
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

        ui_elements::Window("Matrix Game").render([this] {
            ImGuiStyle &style{ImGui::GetStyle()};
            ImVec4 oldImGuiCol_WindowBg = style.Colors[ImGuiCol_WindowBg];
            style.Colors[ImGuiCol_WindowBg] = commons::Colors::BLACK;
            _timer.render();
            _mainMatrix.renderBig();
            ImGui::NewLine();
            ImGui::NewLine();
            for (Matrix matrix: _allMirroredVersions) {
                matrix.renderSmall();
                ImGui::NewLine();
                ImGui::NewLine();
            }

            for (Matrix matrix: _allRotatedVersions) {
                matrix.renderSmall();
                ImGui::NewLine();
                ImGui::NewLine();
            }

            if (_timer.isExpiredNow()) {
                stop();
            }

        });
    }

    void MatrixGame::stop() {
        _endBoxText =
                "Richtige: " + std::to_string(_numberOfCorrectClicksInTotal) + "\nLängster Streak: " +
                std::to_string(_longestStreak);
        _isGameRunning = false;
        _showEndBox = true;
        _endBoxTitle = "Zeit abgelaufen!";
    }

    void MatrixGame::start() {
        reset();
        _mainMatrix.init(7);
        _allMirroredVersions = _mainMatrix.getAllMirroredVersions();
        _allRotatedVersions = _mainMatrix.getAllRotatedVersions();
        _isGameRunning = true;
        _showEndBox = false;
        _timer.start();
    }

    void MatrixGame::reset() {

    }

    void MatrixGame::updateStatistics() {

    }
} // games