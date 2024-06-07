#include <random>
#include <iostream>
#include "ColorMatch.hpp"
#include "../../commons/ColorTheme.hpp"
#include "../../commons/ColorHelper.hpp"
#include "../../commons/Fonts.hpp"

void color_match::ColorMatch::render() {
    start();
}

void color_match::ColorMatch::start() {
    ImGui::Begin("Color Match Game"); // TODO: use Window class
    ImGui::SetWindowSize(ImVec2(400, 400), ImGuiCond_Always);
    if (isTimeForNewRandomColors) {
        pickRandomColorsText();
        pickRandomColorsImVec4();
        isTimeForNewRandomColors = false;
    }
    displayRandomColors();
    displayColorButtons();
    ImGui::End();
}

void color_match::ColorMatch::pickRandomColorsText() {
    randomColorsText.clear();
    for (int i{0}; i < numberOfRandomColors; i++) {
        randomColorsText.emplace_back(getRandomElement(_AVAILABLE_COLORS_TEXT));
    }
}

void color_match::ColorMatch::pickRandomColorsImVec4() {
    randomColorsImVec4.clear();
    for (int i{0}; i < numberOfRandomColors; i++) {
        randomColorsImVec4.emplace_back(getRandomElement(_AVAILABLE_COLORS_IMVEC4));
    }
}

void color_match::ColorMatch::displayRandomColors() {
    ImGui::PushFont(commons::Fonts::_header3);
    for (int i{0}; i < randomColorsText.size(); i++) {
        ImGui::PushStyleColor(ImGuiCol_Text, randomColorsImVec4.at(i));
        ImGui::Text("%s", randomColorsText.at(i).c_str());
        ImGui::SameLine();
        ImGui::PopStyleColor();
    }
    ImGui::PopFont();
}

void color_match::ColorMatch::displayColorButtons() {
    ImGui::NewLine();
    for (int i{0}; i < _AVAILABLE_COLORS_TEXT.size(); i++) {
        if (indexOfCurrentColor >= numberOfRandomColors) {
            isTimeForNewRandomColors = true;
            indexOfCurrentColor = 0;
        }
        bool isCurrentColor = _AVAILABLE_COLORS_TEXT.at(i) == randomColorsText.at(indexOfCurrentColor);
        ImGui::PushStyleColor(ImGuiCol_Button, _AVAILABLE_COLORS_IMVEC4.at(i)); // Normal state
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, _AVAILABLE_COLORS_IMVEC4.at(i)); // Hover state
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                              isCurrentColor ? commons::ColorTheme::SUCCESS_COLOR : commons::ColorTheme::ERROR_COLOR);
        if (ImGui::Button(_AVAILABLE_COLORS_TEXT.at(i).c_str())) {
            if (isCurrentColor) {
                indexOfCurrentColor++;
                numberOfCorrectClicksInTotal++;
                numberOfCorrectClicksSinceLastError++;
            } else {
                numberOfCorrectClicksSinceLastError--;
            };
        }
        ImGui::PopStyleColor(3);
        ImGui::SameLine();
    }
}

void color_match::ColorMatch::reset() {
    isTimeForNewRandomColors = true;
    indexOfCurrentColor = 0;
    numberOfCorrectClicksInTotal = 0;
    numberOfCorrectClicksSinceLastError = 0;
}






