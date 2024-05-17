#include "Header.hpp"

#include <utility>
#include "Window.hpp"

#pragma once

Header::Header(std::string  left, std::string  right, std::function<void()> callback)
        : leftText(std::move(left)), rightButtonText(std::move(right)), buttonClickCallback(std::move(callback)) {
    centerText = "Human Benchmark";
}

void Header::render() {
    ui_elements::Window("Header").render([this](){
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
    });
}
