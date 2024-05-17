#include "Header.hpp"

void Header::CustomButton(const char* label) {
    ImVec4 buttonColor = ImVec4(0.4f, 0.6f, 1.0f, 1.0f); // Blue color
    ImVec4 textColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);   // Black color
    ImVec4 borderColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // Black border color

    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, buttonColor);
    ImGui::PushStyleColor(ImGuiCol_Text, textColor);
    ImGui::PushStyleColor(ImGuiCol_Border, borderColor);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f); // Rounded corners
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f); // Border size

    if (ImGui::Button(label)) {
        // Button click action
    }

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(5);
}