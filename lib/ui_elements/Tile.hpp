#pragma once

#include "UiElement.hpp"
#include <string>
#include <functional>
#include <imgui.h>

namespace ui_elements {
    /**************************************************************
     * On the dashboard, there is a tile for each game.
     * A Tile contains an icon for the game, the name of the game
     * and a short description. By clicking on the tile, the game
     * can be started.
     **************************************************************/
    class Tile : public UiElement {
        float _height{300};
        float _width{400};
        std::string _pictogram;
        std::string _gameName;
        std::string _description;
        std::string _buttonText;
        std::function<void()> _onClick;

        void setButtonText();

    public:
        // Constructors
        Tile() = delete;  // Delete the default constructor
        explicit Tile(std::string pic, std::string name, std::string desc, std::function<void()> onClick);

        // Render method
        void render() const override;
    };
}
