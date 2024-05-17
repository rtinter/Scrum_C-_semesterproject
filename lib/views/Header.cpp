#include "Header.hpp"
#pragma once

Header::Header(const std::string& left, const std::string& right, std::function<void()> callback)
        : leftText(left), rightButtonText(right), buttonClickCallback(callback) {
}


void Header::render() {
    ImGui::Text("%s", leftText.c_str());
    ImGui::SameLine(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(centerText.c_str()).x / 2);
    ImGui::Text("%s", centerText.c_str());
    ImGui::SameLine(ImGui::GetIO().DisplaySize.x - ImGui::CalcTextSize(rightButtonText.c_str()).x - 10);
    if (ImGui::Button(rightButtonText.c_str())) {
        if (buttonClickCallback) {
            buttonClickCallback();
        }
    }
}
