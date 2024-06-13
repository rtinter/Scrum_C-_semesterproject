#include "Matrix.hpp"
#include <cstdlib>
#include "imgui.h"
#include "Colors.hpp"

void Matrix::init() {
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            _data[i][j] = rand() % 3 == 0; // set about 33% of the cells 'true'
        }
    }
}

void Matrix::render(float const cellSize) {
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

Matrix Matrix::getRotatedCopy() {
    Matrix rotatedMatrix;
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            rotatedMatrix._data[j][_SIZE - 1 - i] = _data[i][j];
        }
    }
    return rotatedMatrix;
}

Matrix Matrix::getMirroredCopy() {
    Matrix mirroredMatrix;
    for (int i{0}; i < _SIZE; ++i) {
        for (int j{0}; j < _SIZE; ++j) {
            bool temp = _data[i][j];
            mirroredMatrix._data[i][j] = _data[i][_SIZE - 1 - j];
        }
    }
    return mirroredMatrix;
}
