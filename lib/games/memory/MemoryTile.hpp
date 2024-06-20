#pragma once
#include "Tile.hpp"
#include <string>
#include <functional>
#include <imgui.h>
#include <Colors.hpp>
#include <SFML/Graphics.hpp>

namespace memory {

    class MemoryTile : public ui_elements::Tile {
    private:
        bool _isFlipped{false};
        sf::Texture _frontTexture;
        ImVec4 _backColor{commons::Colors::RICH_YELLOW};
        std::function<void()> _onClick;
        ImVec2 _size;
        int _index;

    public:
        MemoryTile(sf::Texture const &frontTexture, std::function<void()> const &onClick, ImVec2 const &size, int index);

        void render() override;

        void flip();

        void reset();

        bool isFlipped() const;

        void setBackColor(ImVec4 color); //unused

        ImVec4 getBackColor() const; //unused

        int getIndex() const; // Add getter for index
    };
} // namespace memory