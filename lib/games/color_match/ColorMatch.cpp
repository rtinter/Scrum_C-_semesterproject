#include <random>
#include <iostream>
#include "ColorMatch.hpp"
#include "../../commons/Colors.hpp"

void color_match::ColorMatch::render() {
    bool showGame{true};

    if (showGame) {
        start();
    }
}

void color_match::ColorMatch::start() {

    ImGui::Begin("Color Match Game"); // TODO: use Window class
    ImGui::SetWindowSize(ImVec2(400, 400), ImGuiCond_Always);

    if (isTimeForNewColors) {
        chooseColorsText();
        chooseColorsImVec4();
        isTimeForNewColors = false;
    }
    displayChosenColors();


    ImGui::End();


}

void color_match::ColorMatch::reset() {

}


void color_match::ColorMatch::chooseColorsText() {
    chosenColorsText.clear();
    for (int i = 0; i < numberOfColorsToChoose; i++) {
        std::cout << getRandomElement(_AVAILABLE_COLORS_TEXT);
        chosenColorsText.emplace_back(getRandomElement(_AVAILABLE_COLORS_TEXT));
    }
}

void color_match::ColorMatch::chooseColorsImVec4() {
    chosenColorsImVec4.clear();
    for (int i = 0; i < numberOfColorsToChoose; i++) {
        chosenColorsImVec4.emplace_back(getRandomElement(_AVAILABLE_COLORS_IMVEC4));
    }
}


void color_match::ColorMatch::displayChosenColors() {
    for (int i = 0; i < chosenColorsText.size(); i++) {
        ImGui::PushStyleColor(ImGuiCol_Text, chosenColorsImVec4[i]);
        ImGui::Text(chosenColorsText.at(i));
        ImGui::PopStyleColor();
    }
}



