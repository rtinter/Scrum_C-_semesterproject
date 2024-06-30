#include "StatisticsGameTable.hpp"

#include <ColorTheme.hpp>
#include <Fonts.hpp>
#include <iomanip>
#include <unordered_map>
#include <ostream>
#include <iostream>

namespace ui_elements {
    StatisticsGameTable::StatisticsGameTable(
            std::map<int, //Reihenfolge in der die Tabelle angezeigt wird 0. Wert Überschrift
                    std::vector<std::string> > input) {
        _input = input;
        if (input.empty()) {
            _column_size = 0;
        } else {
            _column_size = _input.begin()->second.size();
        }
    }

    std::string timePointToString(const std::chrono::system_clock::time_point &tp) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d.%m.%Y %H:%M Uhr");
        return oss.str();
    }

    void StatisticsGameTable::defaultTable() const {
        if (ImGui::BeginTable("Tabelle", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY)) {
            ImGui::PushFont(commons::Fonts::_header2);
            // Kopfzeile
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
        // Kopfzeile
        for (auto const &entry: _input.begin()->second) {
            ImGui::TableSetupColumn(entry.c_str());
        }
        ImGui::TableHeadersRow();
        ImGui::PopFont();

    }

    void StatisticsGameTable::createTableRows() const {
        for (auto const &keyvaluepair: _input) {
            if (_input.begin()->first == keyvaluepair.first) {
                continue; //skips the Tablehead
            }
            ImGui::TableNextRow();
            ImGui::PushFont(commons::Fonts::_header3);
            int i{0};
            for (auto const &entry: keyvaluepair.second) {
                //Datum
                ImGui::TableSetColumnIndex(i);
                //checks if vector has to few data sets
                if (i < _column_size) {
                    ImGui::Text(entry.c_str());
                } else { //if so leaves the column empty
                    ImGui::Text("");
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
