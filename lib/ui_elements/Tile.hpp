#include "UiElement.hpp"
#include <string>
#include <imgui.h>

#pragma once

namespace ui_elements {

    class Tile : public UiElement {
        float _height{300};
        float _width{400};
        std::string _pictogram;
        std::string _gameName;
        std::string _description;
        std::string _buttonText;

        // Setter-Methoden in den privaten Bereich verschieben
        void setButtonText();

    public:
        // Konstruktor
        Tile() = delete;

        explicit Tile(std::string pic, std::string name, std::string desc);

        // Render-Methode
        void render() const override;
    };


}
