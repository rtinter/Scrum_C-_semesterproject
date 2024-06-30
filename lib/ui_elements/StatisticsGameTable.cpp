#include "StatisticsGameTable.hpp"

#include <ColorTheme.hpp>
#include <Fonts.hpp>

namespace ui_elements {

    /**
     * @brief Constructor for StatisticsGameTable.
     *
     * @param input Map aus int und Liste von Strings (Reihenfolge und Zeile an Strings)
     * Der int gibt die Sortierung der Zeilen an (Niedrigste ist die höchste).
     * Die Liste von Strings entspricht einer Zeile, pro Spalte ein String.
     */
    StatisticsGameTable::StatisticsGameTable(std::map<int, std::vector<std::string>> const &input) {
        _input = input;
        if (input.empty()) {
            _column_size = 0;
        } else {
            _column_size = _input.begin()->second.size();
        }
    }

    void StatisticsGameTable::defaultTable() {
        if (ImGui::BeginTable("Tabelle", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY)) {
            ImGui::PushFont(commons::Fonts::_header2);
            // column names
            ImGui::StyleColorsClassic();
            ImGui::TableSetupColumn("Datum");
            ImGui::TableSetupColumn("Dauer");
            ImGui::TableSetupColumn("Session");
            ImGui::TableSetupColumn("Werte");
            ImGui::TableHeadersRow();
            ImGui::PopFont();
            ImGui::EndTable();
        }
    }

    void StatisticsGameTable::createTableHead() const {

        ImGui::PushFont(commons::Fonts::_header3);
        // column names
        for (auto const &entry: _input.begin()->second) {
            ImGui::TableSetupColumn(entry.c_str());
        }
        ImGui::TableHeadersRow();
        ImGui::PopFont();

    }

    void StatisticsGameTable::createTableRows() const {
        for (auto const &keyvaluepair: _input) {
            if (_input.begin()->first == keyvaluepair.first) {
                continue; //skips the table head
            }
            ImGui::TableNextRow();
            ImGui::PushFont(commons::Fonts::_header3);
            int i{0};
            for (auto const &entry: keyvaluepair.second) {
                // date
                ImGui::TableSetColumnIndex(i);
                //checks if vector has to few data sets
                if (i < _column_size) {
                    ImGui::Text("%s", entry.c_str());
                } else {
                    // else leave the column empty
                }
                i++;
            }
            ImGui::PopFont();
        }
    }

    void StatisticsGameTable::createTable() const {
        if (ImGui::BeginTable("Tabelle", _input.begin()->second.size(),
                              ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY)) {

            ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, commons::ColorTheme::PRIMARY_COLOR);
            createTableHead();

            //TextColor
            ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::RAISIN_BLACK);
            createTableRows();
            ImGui::PopStyleColor(2);
            ImGui::EndTable();
        }
    }

    void StatisticsGameTable::render() {
        //backgroundColor
        ImGui::PushStyleColor(ImGuiCol_WindowBg, commons::ColorTheme::PRIMARY_COLOR);
        if (_input.empty()) {
            //If there are no values we need a default map
            defaultTable();
        } else {
            createTable();
        }
        ImGui::PopStyleColor();
    }
}
