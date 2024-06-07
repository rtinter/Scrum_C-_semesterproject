#include <random>
#include <iostream>
#include "ColorMatch.hpp"
#include "../../commons/ColorTheme.hpp"
#include "../../commons/ColorHelper.hpp"
#include "../../commons/Fonts.hpp"
#include "../../ui_elements/InfoBox.h"

void games::ColorMatch::render() {
    // if (!timer.isRunning() && !timer.isExpired()) {
    //     timer.start();
    // }
    // if (timer.isExpiredNow()) {
    //     std::cout << numberOfCorrectClicksInTotal;
    // }
    //ui_elements::InfoBox(_showInfobox, _NAME, _gameDescription, _gameRules, _gameControls, [this] {
    start();
    //}).render();
}

void games::ColorMatch::start() {
    ImGui::Begin("Color Match Game"); // TODO: use Window class
    ImGui::SetWindowSize(ImVec2(400, 400), ImGuiCond_Always);
    //timer.render();
    if (isTimeForNewRandomColors) {
        pickRandomColorsText();
        pickRandomColorsImVec4();
        isTimeForNewRandomColors = false;
    }
    displayRandomColors();
    displayColorButtons();
    ImGui::End();
}

void games::ColorMatch::pickRandomColorsText() {
    randomColorsText.clear();
    for (int i{0}; i < numberOfRandomColors; i++) {
        randomColorsText.emplace_back(getRandomElement(_AVAILABLE_COLORS_TEXT));
    }
}

void games::ColorMatch::pickRandomColorsImVec4() {
    randomColorsImVec4.clear();
    for (int i{0}; i < numberOfRandomColors; i++) {
        randomColorsImVec4.emplace_back(getRandomElement(_AVAILABLE_COLORS_IMVEC4));
    }
}

void games::ColorMatch::displayRandomColors() { // TODO center texts
    for (int i{0}; i < randomColorsText.size(); i++) {
        ImGui::PushFont(indexOfCurrentColor == i ? commons::Fonts::_header2 : commons::Fonts::_header3);
        ImGui::PushStyleColor(ImGuiCol_Text, randomColorsImVec4.at(i));
        ImGui::Text("%s", randomColorsText.at(i).c_str());
        ImGui::SameLine();
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }

}

void games::ColorMatch::displayColorButtons() {
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

        std::string buttonID = "##" + _AVAILABLE_COLORS_TEXT.at(i);
        if (ImGui::Button(buttonID.c_str(), ImVec2(70, 30))) {

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

void games::ColorMatch::reset() {
    isTimeForNewRandomColors = true;
    indexOfCurrentColor = 0;
    numberOfCorrectClicksInTotal = 0;
    numberOfCorrectClicksSinceLastError = 0;
}

std::string games::ColorMatch::getName() const {
    return _NAME;
}






