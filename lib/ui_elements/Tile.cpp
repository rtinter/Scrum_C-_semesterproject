#include "Tile.hpp"

#include <sstream>

#include "Centered.hpp"
#include "ColorHelper.hpp"
#include "Colors.hpp"
#include "Fonts.hpp"
#include "TextCentered.hpp"


namespace ui_elements {
    // Constructor: Initializes the Tile with the specified icon, name, description, color, and click function
    Tile::Tile(std::string const &pic, std::string const &name, std::string const &desc,
               ImVec4 const &color, std::function<void()> const &onClick)
        : _pictogram(pic), _gameName(name), _description(desc), _buttonColor(color), _onClick(onClick) {
        setButtonText();
    }

    // Sets the text of the button based on the game name, description, and pictogram
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

    // Renders the tile
    void Tile::render() {
        ImGui::SetNextWindowSize(ImVec2(this->_width, this->_height), ImGuiCond_Always);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 7.0f);

        // Adjust the background color based on hover state
        if (_isHovered) {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = commons::ColorHelper::adjustBrightness(_buttonColor, 1.2);
        } else {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = _buttonColor;
        }

        // Begin the child window
        ImGui::BeginChild(_gameName.c_str(), ImVec2(this->_width, this->_height), true,
                          ImGuiWindowFlags_AlwaysAutoResize);
        _isHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows);
        if (_isHovered) {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = sf::Color::Blue;

            // If the left mouse button is clicked, trigger the onClick function
            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                if (_onClick) _onClick();
            }
        }

        // Center the content within the child window
        Centered(true, true, [*this] {
            ImGui::GetStyle().Colors[ImGuiCol_ChildBg] = commons::Colors::TRANSPARENT;

            // Render the pictogram
            ImGui::PushFont(commons::Fonts::_iconRegular);
            TextCentered(_pictogram.c_str());
            ImGui::PopFont();

            // Render the game name
            ImGui::PushFont(commons::Fonts::_header2);
            TextCentered(_gameName.c_str());
            ImGui::PopFont();

            // Render the description
            TextCentered(_description.c_str());
        });

        ImGui::EndChild(); // End the child window
        ImGui::PopStyleVar(); // Pop the style variable for child rounding
    }
} // ui_elements
