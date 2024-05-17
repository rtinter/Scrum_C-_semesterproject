#include "Header.hpp"
#pragma once

Header::Header(const std::string& left, const std::string& right, std::function<void()> callback)
        : leftText(left), rightButtonText(right), buttonClickCallback(callback) {
    centerText = "Human Benchmark";
}

void Header::render() {
    ImGui::Begin("Header", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 50), ImGuiCond_Always);

    ImGui::Text("%s", leftText.c_str());
    ImGui::SameLine(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(centerText.c_str()).x / 2);
    ImGui::Text("%s", centerText.c_str());
    ImGui::SameLine(ImGui::GetIO().DisplaySize.x - ImGui::CalcTextSize(rightButtonText.c_str()).x - 10);
    if (ImGui::Button(rightButtonText.c_str())) {
        if (buttonClickCallback) {
            buttonClickCallback();
        }
    }

    ImGui::End();
}
