#include "Tile.hpp"

#include <Centered.hpp>
#include <ColorHelper.hpp>
#include <Fonts.hpp>
#include <sstream>
#include <TextCentered.hpp>


namespace ui_elements {
    // Konstruktor
    Tile::Tile(std::string const &pic, std::string const &name, std::string const &desc,
               std::function<void()> const &onClick)
        : _pictogram(pic), _gameName(name), _description(desc), _onClick(onClick) {
        setButtonText();
    }

    Tile::Tile(std::string const &pic, std::string const &name, std::string const &desc,
               ImVec4 const &color, std::function<void()> const &onClick)
        : _pictogram(pic), _gameName(name), _description(desc), _buttonColor(color), _onClick(onClick) {
        setButtonText();
    }

    // Setter-Methode für den Button-Text
    void Tile::setButtonText() {
        std::stringstream ss;
        if (!_pictogram.empty()) {
            ss << _pictogram << "\n";
        }
        ss << _gameName << "\n";
        if (!_description.empty()) {
            ss << "\n" << _description;
        }
        _buttonText = ss.str();
    }

    // Render-Methode
    void Tile::render() {
        ImGui::SetNextWindowSize(ImVec2(this->_width, this->_height), ImGuiCond_Always);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 7.0f);

        if (_isHovered) {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = commons::ColorHelper::adjustBrightness(_buttonColor, 1.2);
        } else {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = _buttonColor;
        }
        ImGui::BeginChild(_gameName.c_str(), ImVec2(this->_width, this->_height), true,
                          ImGuiWindowFlags_AlwaysAutoResize);
        _isHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);
        if (_isHovered) {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = sf::Color::Blue;

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                if (_onClick) _onClick();
            }
        }

        Centered(true, true, [*this] {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = commons::Colors::TRANSPARENT;

            ImGui::PushFont(commons::Fonts::_iconRegular);
            TextCentered(_pictogram.c_str());
            ImGui::PopFont();

            ImGui::PushFont(commons::Fonts::_header2);
            TextCentered(_gameName.c_str());
            ImGui::PopFont();

            TextCentered(_description.c_str());
        });

        ImGui::EndChild();
        ImGui::PopStyleVar();
    }
}
