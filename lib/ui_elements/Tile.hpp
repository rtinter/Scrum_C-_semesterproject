#pragma once

#include <Colors.hpp>
#include <ColorTheme.hpp>
#include <string>
#include <functional>
#include <imgui.h>
#include <UiElement.hpp>


namespace ui_elements {
    /**
     * @brief Represents a tile on the dashboard for each game.
     * A tile contains an icon for the game, the name of the game,
     * and a short description. By clicking on the tile, the game can be started.
     */
    class Tile : public UiElement {
        float _height{300.0F};
        float _width{400.0F};
        std::string _pictogram;
        std::string _gameName;
        std::string _description;
        std::string _buttonText;
        ImVec4 _buttonColor{commons::ColorTheme::PRIMARY_COLOR};
        bool _isHovered{false};

        std::function<void()> _onClick;

        /**
         * @brief Sets the text of the button based on the game name.
         */
        void setButtonText();

    public:
        // Constructors
        Tile() = delete;

        /**
      * @brief Constructs a tile with specified icon, name, description, color, and click function.
      * @param pic Icon for the game.
      * @param name Name of the game.
      * @param desc Description of the game.
      * @param color Color of the button.
      * @param onClick Function to call when the tile is clicked.
      */
        explicit Tile(std::string const &pic, std::string const &name, std::string const &desc,
                      ImVec4 const &color, std::function<void()> const &onClick);


        /**
         * @brief Renders the tile.
         */
        void render() override;
    };
}
