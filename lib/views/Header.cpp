#include "Header.hpp"
#include <utility>
#include "Window.hpp"

Header::Header(std::string left, std::string right, std::function<void()> callback)
        : leftText(std::move(left)), rightButtonText(std::move(right)), buttonClickCallback(std::move(callback)) {
    centerText = "Human Benchmark";
}

void Header::render() {
    ui_elements::Window("Header").render([this](){
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, headerHeight + topMargin + bottomMargin), ImGuiCond_Always);

        // Vertikale Abstände
        ImGui::SetCursorPosY(topMargin);

        // Linker Text
        ImGui::SetCursorPosX(sideMargin);
        ImGui::Text("%s", leftText.c_str());

        // Zentraler Text
        ImGui::SameLine(ImGui::GetIO().DisplaySize.x / 2 - ImGui::CalcTextSize(centerText.c_str()).x / 2);
        ImGui::Text("%s", centerText.c_str());

        // Rechter Button mit Margin
        ImGui::SameLine(ImGui::GetIO().DisplaySize.x - ImGui::CalcTextSize(rightButtonText.c_str()).x - sideMargin);
        if (ImGui::Button(rightButtonText.c_str())) {
            if (buttonClickCallback) {
                buttonClickCallback();
            }
        }

        // Vertikale Abstände
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + bottomMargin);
    });
}
