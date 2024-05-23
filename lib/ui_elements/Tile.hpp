#include "UiElement.hpp"
#include <string>
#include <imgui.h>
#pragma once

namespace ui_elements {

    class Tile : public UiElement {
        float height {300};
        float width {400};
        std::string pictogram;
        std::string gameName;
        std::string description;
        std::string buttonText;

        // Setter-Methoden in den privaten Bereich verschieben
        void setButtonText();

    public:
        // Konstruktor
        Tile() = delete;
        explicit Tile(const std::string& pic, const std::string& name, const std::string& desc);

        // Render-Methode
        void render() const override;
    };


}
