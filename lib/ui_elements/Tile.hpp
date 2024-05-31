#include "UiElement.hpp"
#include <string>
#include <functional>
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
        std::function<void()> _onClick;

        void setButtonText();

    public:
        // Constructors
        Tile() = delete;

        explicit Tile(std::string const &pic, std::string const &name, std::string const &desc,
                      std::function<void()> const &onClick);

        // Render method
        void render() const override;
    };
}
