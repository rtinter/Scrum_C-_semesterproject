#include "Matrix.hpp"
#include <cstdlib>
#include <array>
#include "imgui.h"
#include "Colors.hpp"

void Matrix::init() {
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            _data[i][j] = rand() % 3 == 0; // set about 33% of the cells 'true'
        }
    }
}

void Matrix::render(float const cellSize) const {
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec2 oldItemSpacing = style.ItemSpacing;
    style.ItemSpacing = ImVec2(0, 0);
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            ImGui::PushID(i * _SIZE + j); // ensure unique ID
            if (_data[i][j]) {
                ImGui::ColorButton("##btn", commons::Colors::BRIGHT_GREEN, ImGuiColorEditFlags_NoTooltip,
                                   ImVec2(cellSize, cellSize));
            } else {
                ImGui::ColorButton("##btn", commons::Colors::BLACK, ImGuiColorEditFlags_NoTooltip,
                                   ImVec2(cellSize, cellSize));
            }
            ImGui::PopID();
            if (j < _SIZE - 1) ImGui::SameLine();
        }
    }
    style.ItemSpacing = oldItemSpacing;

}

std::array<Matrix, 2> Matrix::getAllMirroredVersions() {
    return std::array<Matrix, 2>{mirrorHorizontally(), mirrorVertically()};
}

std::array<Matrix, 3> Matrix::getAllRotatedVersions() {
    return std::array<Matrix, 3>{rotate90DegreesRight(1), rotate90DegreesRight(2), rotate90DegreesRight(3)};
}

Matrix Matrix::rotate90DegreesRight(int const nTimes) {
    Matrix rotatedMatrix = *this; // copy original matrix
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

Matrix Matrix::mirrorHorizontally() {
    Matrix mirroredMatrix;
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            mirroredMatrix._data[i][j] = _data[_SIZE - 1 - i][j];
        }
    }
    return mirroredMatrix;
}

Matrix Matrix::mirrorVertically() {
    Matrix mirroredMatrix;
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            mirroredMatrix._data[i][j] = _data[i][_SIZE - 1 - j];
        }
    }
    return mirroredMatrix;
}

