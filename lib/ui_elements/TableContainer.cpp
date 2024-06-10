//
// Created by samtf on 07.06.2024.
//

#include "TableContainer.h"

#include <Colors.hpp>
#include <iostream>

#include "imgui_internal.h"
#include "Window.hpp"
#include "Fonts.hpp"

namespace ui_elements {

    TableContainer::TableContainer(std::string const &gameName, StatisticsGameTable const &statisticsGameTable)
            : _gameName{gameName}, _statisticsGameTable{statisticsGameTable} {}


    void TableContainer::render() {

        float childWidth{ImGui::GetContentRegionAvail().x * 0.5f};
        float childHeight{400.f};

        ImGui::BeginChild(_gameName.c_str(), ImVec2(childWidth, childHeight), true, ImGuiWindowFlags_AlwaysAutoResize);
       //ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Black);
       ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::DARK_GRAY);

        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::Text("Spiel %s", _gameName.c_str());

        _statisticsGameTable.render();


        ImGui::PopStyleColor();
        ImGui::PopFont();
        ImGui::EndChild();



        /*  ImGui::BeginChild(_gameName.c_str(), ImVec2(_width, _height),
                            true);
          ImGui::PushStyleColor(ImGuiCol_ButtonHovered, sf::Color::Blue);
          std::cout << ImGui::GetCurrentWindow()->Name << std::endl;
          const char *name = ImGui::GetCurrentWindow()->Name;
          // Begin the table

          _statisticsGameTable.render();

          //_statisticsGameTable.render();
          // Output the window properties
          ImGui::Text("Current Window Name: %s", name);
          ImGui::PopStyleColor();
          ImGui::EndChild();
          /*ui_elements::Window(_gameName).render([this](){

              ImGui::BeginChild(_gameName.c_str(), ImVec2(_width, _height),
                                   true);

              ImGui::SetWindowPos(ImVec2(100, 100), ImGuiCond_Always);
              ImGui::PushStyleColor(ImGuiCol_WindowBg, commons::Colors::Colors::LIGHT_GRAY);

              ImGui::PushFont(commons::Fonts::_header2);
          ImGuiWindow* window = ImGui::GetCurrentWindow();
              ImVec2 pos = ImGui::GetWindowPos();
               ImVec2 size = ImGui::GetWindowSize();
               const char* name = ImGui::GetCurrentWindow()->Name;

               // Output the window properties
               ImGui::Text("Current Window Name: %s", name);
               ImGui::Text("Window Position: (%.0f, %.0f)", pos.x, pos.y);
               ImGui::Text("Window Size: (%.0f, %.0f)", size.x, size.y);
         // Output the window name
              ImGui::Text("Current Window Name: %s", window->Name);
              ImGui::Text(_gameName.c_str());
              ImGui::PopFont();
              ImGui::PopStyleColor();

          });*/
        /*ImGuiWindow *window = ImGui::GetCurrentWindow();
        std::cout << ImGui::GetCurrentWindow()->Name << std::endl; */
    }
} // ui_elements