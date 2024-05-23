#include "UiElement.hpp"
#include <string>
#include <imgui.h>

#pragma once

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

        void setButtonText();

    public:
        // Konstruktor
        Tile() = delete;
        explicit Tile(std::string pic, std::string name, std::string desc);

        // Render-Methode
        void render() const override;
    };


}
