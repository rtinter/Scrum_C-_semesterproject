#include "MatrixGame.hpp"
#include "Window.hpp"
#include "InfoBox.hpp"
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "RandomPicker.hpp"
#include "Centered.hpp"
#include "ColorTheme.hpp"

namespace game {

    MatrixGame::MatrixGame() : Game(abstract_game::GameID::MATRIX) {
        _gameName = "Matrix";
        _gameDescription =
                "Das Spiel 'Matrix' trainiert das räumliche Vorstellungsvermögen";
        _gameRules = "Finde in der unteren Zeile die gedrehte/gespiegelte Version der oberen Matrix";
        _gameControls = "Linke Maustaste: Klicke auf die richtige Matrix in der unteren Zeile";
        _nColoredCellsMax = Matrix::getSize() * Matrix::getSize() / 2;
        _nColoredCellsMin = Matrix::getSize();
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
                float displayedSize = Matrix::getSize() * Matrix::getCellSizeSmall();
                for (int i{0}; i < _allRotatedVersions.size(); i++) {
                    ImGuiStyle &style{ImGui::GetStyle()};
                    ImVec2 oldItemSpacing{style.ItemSpacing};
                    style.ItemSpacing = ImVec2(0, 0);
                    float oldFrameRounding{style.FrameRounding};
                    style.FrameRounding = 0.f;

                    // create transparent button
                    ImGui::PushStyleColor(ImGuiCol_Button, commons::Colors::NONE);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, commons::Colors::NONE);
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, commons::ColorTheme::SUCCESS_COLOR);
                    float const margin{4.f}; // button should overlap matrix a little bit
                    std::string buttonId{"buttonForMatrix" + std::to_string(i)};
                    if (ImGui::Button(buttonId.c_str(), ImVec2(displayedSize + margin, displayedSize + margin))) {
                        std::cout << i;
                        _nCorrectClicksInTotal++;
                    }
                    ImGui::PopStyleColor(3); // pop ImGuiCol_Button(Hovered/Active)

                    // display matrix at same position (= covered by transparent button)
                    ImVec2 cursorPosition = ImGui::GetCursorPos();
                    cursorPosition.y -= displayedSize + margin / 2;
                    cursorPosition.x += margin / 2;

                    ImGui::SetCursorPos(cursorPosition);
                    _allRotatedVersions[i].renderSmall();
                    style.ItemSpacing = oldItemSpacing;
                    style.FrameRounding = oldFrameRounding;

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

    }
} // game