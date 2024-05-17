#include "Tile.h"

namespace ui_elements {

    // Konstruktor
    Tile::Tile(int h, int w, ImVec4 c, const std::string &pic, const std::string &name, const std::string &desc)
            : height(h), width(w), color(c), pictogram(pic), gameName(name), description(desc) {}

    // Setter-Methoden
    void Tile::setHeight(int h) {
        height = h;
    }

    void Tile::setWidth(int w) {
        width = w;
    }

    void Tile::setPictogram(const std::string &pic) {
        pictogram = pic;
    }

    void Tile::setGameName(const std::string &name) {
        gameName = name;
    }

    void Tile::setDescription(const std::string &desc) {
        description = desc;
    }

    // Getter-Methoden
    int Tile::getHeight() const {
        return height;
    }

    int Tile::getWidth() const {
        return width;
    }

    const std::string &Tile::getPictogram() const {
        return pictogram;
    }

    const std::string &Tile::getGameName() const {
        return gameName;
    }

    const std::string &Tile::getDescription() const {
        return description;
    }

    ImVec4 Tile::getColor() const {
        return color;
    }

    // Render-Methode
    void Tile::render() {
        ImGui::PushStyleColor(ImGuiCol_Button, color);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(color.x + 0.1f, color.y + 0.1f, color.z + 0.1f, color.w));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(color.x - 0.1f, color.y - 0.1f, color.z - 0.1f, color.w));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);

        ImGui::BeginChild("Tile", ImVec2(width, height), true, ImGuiWindowFlags_NoScrollbar);

        ImGui::Dummy(ImVec2((width - 100) / 2, 20)); // Platz für zentriertes Piktogramm
        ImGui::Button(pictogram.c_str(), ImVec2(100, 50)); // Piktogramm

        ImGui::Dummy(ImVec2((width - ImGui::CalcTextSize(gameName.c_str()).x) / 2, 20)); // Platz für zentrierten Namen
        ImGui::Text("%s", gameName.c_str()); // Spielname

        ImGui::Dummy(ImVec2((width - ImGui::CalcTextSize(description.c_str()).x) / 2,
                            10)); // Platz für zentrierte Beschreibung
        ImGui::Text("%s", description.c_str()); // Beschreibung

        ImGui::EndChild();

        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar();
    }
}