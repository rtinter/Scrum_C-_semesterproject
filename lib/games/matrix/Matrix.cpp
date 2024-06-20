#include "Matrix.hpp"
#include <array>
#include <iostream>
#include "imgui.h"
#include "Colors.hpp"
#include "Fonts.hpp"
#include "RandomPicker.hpp"
#include "imgui_internal.h"

/**************************************
 * init() fills the matrix with values
 * @param nCellsWithNumbers
 **************************************/
void Matrix::init(int nCellsWithNumbers) {
    // check if nColoredCells is within a reasonable range
    if (nCellsWithNumbers < SIZE || nCellsWithNumbers > SIZE * SIZE / 2) {
        throw std::invalid_argument("nColoredCells has to be between [_SIZE] and [_SIZE * _SIZE / 2]");
    }
    // set all cells to 0
    for (int i{0}; i < SIZE; ++i) {
        for (int j{0}; j < SIZE; ++j) {
            _data[i][j] = 0; // O represents an 'empty' cell
        }
    }

    // color some cells
    for (int n{0}; n < nCellsWithNumbers; ++n) {
        bool isFilled{false};
        while (!isFilled) {
            int x{commons::RandomPicker::randomInt(0, SIZE - 1)};
            int y{commons::RandomPicker::randomInt(0, SIZE - 1)};
            if (_data[x][y] == 0) { // only add number != 0 when not already filled
                // the numbers from 100 to 103 represent different color shades
                if (n % 2 == 0) {
                    //  10, 20, 30, 40 represent "0" in different color shades
                    _data[x][y] = commons::RandomPicker::pickRandomElement(std::vector<int>{10, 20, 30, 40});
                } else {
                    //  11, 21, 31, 41 represent "1" in different color shades
                    _data[x][y] = commons::RandomPicker::pickRandomElement(std::vector<int>{11, 21, 31, 41});

                }
                isFilled = true;

            }
        }
    }
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
    ImGui::BeginGroup();
    for (int i{0}; i < SIZE; ++i) {
        for (int j{0}; j < SIZE; ++j) {
            ImGui::PushID(i * SIZE + j); // ensure unique ID
            ImVec4 buttonColor{commons::Colors::BLACK};
            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColor);
            if (0 == _data[i][j]) { // 0 represents 'empty' cell
                ImGui::Button("", ImVec2(cellSize, cellSize));
            } else {
                char const *buttonText;
                if (_data[i][j] % 10 == 0) {
                    buttonText = "0";
                } else {
                    buttonText = "1";
                }

                ImVec4 textColor;
                if (_data[i][j] <= 11) {
                    textColor = commons::Colors::BRIGHT_GREEN;
                } else if (_data[i][j] <= 21) {
                    textColor = commons::Colors::BRIGHT_GREEN1;
                } else if (_data[i][j] <= 31) {
                    textColor = commons::Colors::BRIGHT_GREEN2;
                } else {
                    textColor = commons::Colors::BRIGHT_GREEN3;
                }

                ImGui::PushStyleColor(ImGuiCol_Text, textColor);
                ImGui::Button(buttonText, ImVec2(cellSize, cellSize));
                ImGui::PopStyleColor(); // pop ImGuiCol_text
            }

            ImGui::PopStyleColor(3); // pop ImGuiCol_Button(Hovered/Active)
            ImGui::PopID();
            if (j < SIZE - 1) ImGui::SameLine();
        }
    }
    ImGui::EndGroup();
    // reset style settings
    style.ItemSpacing = oldItemSpacing;
    style.FrameRounding = oldFrameRounding;
}

/*******************************************************************
 * renderBig() renders this matrix with a large font and large cells
 ********************************************************************/
void Matrix::renderBig() {
    ImGui::PushFont(commons::Fonts::_matrixFontBig);
    render(CELL_SIZE_BIG);
    ImGui::PopFont();
}

/*******************************************************************
 * renderSmall() renders this matrix with a small font and small cells
 ********************************************************************/
void Matrix::renderSmall() {
    ImGui::PushFont(commons::Fonts::_matrixFontSmall);
    render(CELL_SIZE_SMALL);
    ImGui::PopFont();
}

/******************************************************************
 * isEqual(Matrix const &other) checks if the values of this matrix
 * are identical to the values of another matrix
 * @param other the second matrix that should be used for comparison
 * @return boolean value: Are all matrix elements identical?
 *************************************************************/
bool Matrix::isEqual(Matrix const &other) const {
    for (int i{0}; i < SIZE; i++) {
        for (int j{0}; j < SIZE; j++) {
            if (_data[i][j] != other._data[i][j]) return false;
        }
    }
    return true;
}

bool Matrix::isMirroredVersionOf(Matrix const &other) const {
    for (Matrix mirrored: other.getAllMirroredVersions()) {
        if (isEqual(mirrored)) return true;
    }
    return false;
}

bool Matrix::isRotatedVersionOf(Matrix const &other) const {
    for (Matrix rotated: other.getAllRotatedVersions()) {
        if (isEqual(rotated)) return true;
    }
    return false;
}

Matrix Matrix::getAMirroredVersion() const {
    int type{commons::RandomPicker::randomInt(0, 1)};
    return (0 == type) ? mirrorHorizontally() : mirrorVertically();
}

Matrix Matrix::getARotatedVersion() const {
    int times{commons::RandomPicker::randomInt(1, 3)};
    return rotate90DegreesRight(times); // rotated by 90°, 180° or 270°

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
        for (int i{0}; i < SIZE; ++i) {
            for (int j{0}; j < SIZE; ++j) {
                tempMatrix._data[j][SIZE - 1 - i] = rotatedMatrix._data[i][j];
            }
        }
        rotatedMatrix = tempMatrix;
    }
    return rotatedMatrix;
}

Matrix Matrix::mirrorHorizontally() const {
    Matrix mirroredMatrix;
    for (int i{0}; i < SIZE; ++i) {
        for (int j{0}; j < SIZE; ++j) {
            mirroredMatrix._data[i][j] = _data[SIZE - 1 - i][j];
        }
    }
    return mirroredMatrix;
}

Matrix Matrix::mirrorVertically() const {
    Matrix mirroredMatrix;
    for (int i{0}; i < SIZE; ++i) {
        for (int j{0}; j < SIZE; ++j) {
            mirroredMatrix._data[i][j] = _data[i][SIZE - 1 - j];
        }
    }
    return mirroredMatrix;
}

int Matrix::getSize() {
    return SIZE;
}

int Matrix::getCellSizeSmall() {
    return CELL_SIZE_SMALL;
}

