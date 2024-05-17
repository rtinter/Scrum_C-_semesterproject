#include "Dashboard.hpp"

void Dashboard::render() {

    // Render header
    ImGui::SetNextWindowPos(ImVec2(0, 50), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - 50), ImGuiCond_Always);
    ImGui::Begin("Dashboard", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    float windowWidth = ImGui::GetWindowSize().x;
    float buttonWidth = 300.0f;
    float buttonHeight = 200.0f;
    float padding = 10.0f;
    float totalButtonWidth = buttonWidth * 2 + padding;
    float spacing = (windowWidth - totalButtonWidth) / 2.0f;

    // Category 1
    ImGui::Text("Kategorie 1");
    ImGui::Spacing();

    ImGui::SetCursorPosX(spacing);
    if (ImGui::Button("Pictogram\nSpielname\nBeschreibung", ImVec2(buttonWidth, buttonHeight))) {
        // Button 1 action
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(spacing + buttonWidth + padding);
    if (ImGui::Button("Pictogram\nSpielname\nBeschreibung", ImVec2(buttonWidth, buttonHeight))) {
        // Button 2 action
    }

    ImGui::Spacing();
    ImGui::Spacing();

    // Category 2
    ImGui::Text("Kategorie 2");
    ImGui::Spacing();

    ImGui::SetCursorPosX(spacing);
    if (ImGui::Button("Pictogram\nSpielname\nBeschreibung", ImVec2(buttonWidth, buttonHeight))) {
        // Button 3 action
    }

    ImGui::SameLine();
    ImGui::SetCursorPosX(spacing + buttonWidth + padding);
    if (ImGui::Button("Pictogram\nSpielname\nBeschreibung", ImVec2(buttonWidth, buttonHeight))) {
        // Button 4 action
    }

    ImGui::End();
}
