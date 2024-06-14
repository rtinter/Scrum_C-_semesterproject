#include "Matrix.hpp"
#include <array>
#include "imgui.h"
#include "Colors.hpp"
#include "Fonts.hpp"
#include "RandomPicker.hpp"
#include "imgui_internal.h"

/**************************************
 * init() fills the matrix with values
 * @param nColoredCells
 **************************************/
void Matrix::init(int nColoredCells) {
    // check if nColoredCells is within a reasonable range
    if (nColoredCells < _SIZE || nColoredCells > _SIZE * _SIZE / 2) {
        throw std::invalid_argument("nColoredCells has to be between [_SIZE] and [_SIZE * _SIZE / 2]");
    }
    // set all cells to 0
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            _data[i][j] = 0; // O represents an 'empty' cell
        }
    }

    // color some cells
    for (int i{0}; i < nColoredCells; ++i) {
        bool isFilled{false};
        while (!isFilled) {
            int x{commons::RandomPicker::randomInt(0, _SIZE - 1)};
            int y{commons::RandomPicker::randomInt(0, _SIZE - 1)};
            if (_data[x][y] == 0) { // only add number < 1 when not already filled
                // the numbers from 100 to 103 represent different Strings ("0" or "1") in different color shades
                _data[x][y] = commons::RandomPicker::randomInt(100, 103);
                isFilled = true;
            }
        }
    }
}

void Matrix::renderBig() {
    ImGui::PushFont(commons::Fonts::_matrixFontBig);
    render(50);
    ImGui::PopFont();
}

void Matrix::renderSmall() {
    ImGui::PushFont(commons::Fonts::_matrixFontSmall);
    render(30);
    ImGui::PopFont();
}

/***************************************************
 * render() displays each matrix cell as a button
 * @param cellSize
 ***************************************************/
void Matrix::render(float cellSize) {
    // adjust button style (and save old settings)
    ImGuiStyle &style{ImGui::GetStyle()};
    ImVec2 oldItemSpacing{style.ItemSpacing};
    style.ItemSpacing = ImVec2(0, 0);
    float oldFrameRounding{style.FrameRounding};
    style.FrameRounding = 0.f;

    // create a button for each matrix cell
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            ImGui::PushID(i * _SIZE + j); // ensure unique ID
            ImVec4 buttonColor{commons::Colors::BLACK};
            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColor);
            if (0 == _data[i][j]) { // 0 represents 'empty' cell
                if (ImGui::Button("", ImVec2(cellSize, cellSize))) {
                    _isClicked = true;
                }
            } else {
                char const *buttonText;
                ImVec4 textColor;
                switch (_data[i][j]) {
                    // the numbers from 100 to 103 represent different Strings ("0" or "1") in different color shades
                    case 100:
                        textColor = commons::Colors::BRIGHT_GREEN;
                        buttonText = "0";
                        break;
                    case 101:
                        textColor = commons::Colors::BRIGHT_GREEN1;
                        buttonText = "1";
                        break;
                    case 102:
                        textColor = commons::Colors::BRIGHT_GREEN2;
                        buttonText = "0";
                        break;
                    case 103:
                    default:
                        textColor = commons::Colors::BRIGHT_GREEN3;
                        buttonText = "1";
                }
                ImGui::PushStyleColor(ImGuiCol_Text, textColor);
                if (ImGui::Button(buttonText, ImVec2(cellSize, cellSize))) {
                    _isClicked = true;
                }
                ImGui::PopStyleColor(); // pop ImGuiCol_text
            }

            ImGui::PopStyleColor(3); // pop ImGuiCol_Button(Hovered/Active)
            ImGui::PopID();
            if (j < _SIZE - 1) ImGui::SameLine();
        }
    }
    // reset style settings
    style.ItemSpacing = oldItemSpacing;
    style.FrameRounding = oldFrameRounding;

}

std::array<Matrix, 2> Matrix::getAllMirroredVersions() const {
    return std::array<Matrix, 2>{mirrorHorizontally(), mirrorVertically()};
}

std::array<Matrix, 3> Matrix::getAllRotatedVersions() const {
    return std::array<Matrix, 3>{rotate90DegreesRight(1), rotate90DegreesRight(2), rotate90DegreesRight(3)};
}

Matrix Matrix::rotate90DegreesRight(int const nTimes) const {
    Matrix rotatedMatrix{*this}; // copy original matrix
    for (int t{0}; t < nTimes; t++) {
        Matrix tempMatrix;
        for (int i{0}; i < _SIZE; ++i) {
            for (int j{0}; j < _SIZE; ++j) {
                tempMatrix._data[j][_SIZE - 1 - i] = rotatedMatrix._data[i][j];
            }
        }
        rotatedMatrix = tempMatrix;
    }
    return rotatedMatrix;
}

Matrix Matrix::mirrorHorizontally() const {
    Matrix mirroredMatrix;
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            mirroredMatrix._data[i][j] = _data[_SIZE - 1 - i][j];
        }
    }
    return mirroredMatrix;
}

Matrix Matrix::mirrorVertically() const {
    Matrix mirroredMatrix;
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            mirroredMatrix._data[i][j] = _data[i][_SIZE - 1 - j];
        }
    }
    return mirroredMatrix;
}

