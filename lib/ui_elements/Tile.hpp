#pragma once

#include <Colors.hpp>
#include <ColorTheme.hpp>
#include <string>
#include <functional>
#include <imgui.h>
#include <UiElement.hpp>


namespace ui_elements {
    /**************************************************************
     * On the _dashboard, there is a tile for each game.
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
        ImVec4 _buttonColor = commons::ColorTheme::PRIMARY_COLOR;
        bool _isHovered{false};

        std::function<void()> _onClick;

        void setButtonText();

    public:
        // Constructors
        Tile() = delete;

        explicit Tile(std::string const &pic, std::string const &name, std::string const &desc,
                      std::function<void()> const &onClick);

        explicit Tile(std::string const &pic, std::string const &name, std::string const &desc,
                      ImVec4 const &color, std::function<void()> const &onClick);


        // Render method
        void render() override;
    };
}
