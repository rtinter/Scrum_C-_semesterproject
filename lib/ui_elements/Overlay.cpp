//
// Created by zepi on 23.05.24.
//

#include "Overlay.hpp"
#include "imgui.h"

namespace ui_elements {
    Overlay::Overlay(const char *name, bool &showModal) : name(name), showModal(showModal) {

    }

    void Overlay::render() {
        if (showModal) {
            ImGui::SetNextWindowSize(ImVec2(1000, 600));

            ImGui::OpenPopup(name);
            showModal = false;
        }

        if (ImGui::BeginPopupModal(name, nullptr,
                                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                                   ImGuiWindowFlags_NoDecoration)) {

            ImGui::Text("TITEL: Reaktionsspiel");
            ImGui::Text(
                    "SPIELBESCHREIBUNG: Testen und verbessern Sie Ihre Reaktionsgeschwindigkeit, indem Sie so schnell wie möglich auf den Farbwechsel des Bildschirms reagieren.");
            ImGui::Text("SPIELREGELN: Spielstart:\n"
                        "\n"
                        "Starten Sie das Spiel, indem Sie auf die Schaltfläche \"Start\" klicken.\n"
                        "Warten:\n"
                        "\n"
                        "Nachdem Sie das Spiel gestartet haben, wird der Bildschirm in einer neutralen Farbe (z.B. Weiß) angezeigt.\n"
                        "Warten Sie geduldig, bis der Bildschirm seine Farbe wechselt.\n"
                        "Farbwechsel:\n"
                        "\n"
                        "Der Bildschirm wechselt zufällig nach einer bestimmten Zeitspanne seine Farbe (z.B. zu Grün).\n"
                        "Reaktion:\n"
                        "\n"
                        "Sobald der Bildschirm die Farbe wechselt, klicken Sie so schnell wie möglich mit der Maus.\n"
                        "Auswertung:\n"
                        "\n"
                        "Ihre Reaktionszeit wird in Millisekunden gemessen und angezeigt.\n"
                        "Je schneller Ihre Reaktion, desto besser Ihr Ergebnis.");

            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Red);
            if (ImGui::Button("Zurück zum Menü")) {
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("Spiel starten!")) {
                //noch nichts
            }
            ImGui::PopStyleColor();

            ImGui::EndPopup();
        }
    }

} // ui_elements
