
#pragma once
//
// Created by zarathustra on 30.05.24.
//
#include "../commons/Fonts.hpp"
#include "../commons/Colors.hpp"
#include "Window.hpp"
#include "StatisticsGameTable.hpp"
#include <iomanip>
#include <unordered_map>

namespace ui_elements {
    StatisticsGameTable::StatisticsGameTable (std::unordered_map<std::string, //UUID
            std::vector<std::string>> input) {
        _input= input;
    }

    StatisticsGameTable::StatisticsGameTable(std::string datum, std::string dauer, std::string werte) {
        _datum = datum;
        _dauer = dauer;
        _werte = werte;
    }

    std::string timePointToString(const std::chrono::system_clock::time_point& tp) {
        std::time_t t = std::chrono::system_clock::to_time_t(tp);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d.%m.%Y %H:%M Uhr");
        return oss.str();
    }
    void defaultTable(){
        if (ImGui::BeginTable("Tabelle", 4 , ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY )) {
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
            ImGui::PopStyleColor();
        }
    }
    void StatisticsGameTable::createTable() const {
        if (ImGui::BeginTable("Tabelle", _input.begin()->second.size(), ImGuiTableFlags_Borders | ImGuiTableFlags_ScrollY )) {
            ImGui::PushFont(commons::Fonts::_header2);
            // Kopfzeile
            ImGui::StyleColorsClassic();
            for (auto &entry : _input.begin()->second){
                ImGui::TableSetupColumn(entry.c_str());
            }
            ImGui::TableHeadersRow();
            ImGui::PopFont();
            //TextColor
            ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::kDARK_GRAY);

            for (auto &keyvaluepair : _input) {
                if (_input.begin()->first==keyvaluepair.first){
                    continue; //skips the Tablehead
                }
                ImGui::TableNextRow();
                ImGui::PushFont(commons::Fonts::_header3);
                int i = 0;
                for(auto &entry : keyvaluepair.second){
                    //Datum
                    ImGui::TableSetColumnIndex(i);
                    ImGui::Text(entry.c_str());
                    i++;
                }
                ImGui::PopFont();
            }
            ImGui::PopStyleColor(2);
            ImGui::EndTable();
        }
    }

    void StatisticsGameTable::render() const {
        ui_elements::Window("Dashboard").render([this](){
            //backgroundColor
            ImGui::PushStyleColor(ImGuiCol_WindowBg, commons::Colors::Colors::kLIGHT_GRAY);
            if (_input.empty()){    //If there are no values we need a default map
                defaultTable();
            }
           else{
               createTable();//

           }

        });
    }
}


