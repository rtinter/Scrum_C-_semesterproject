//
// Created by Admin on 16.06.2024.
//

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
        std::string _frontImage;
        ImVec4 _backColor{commons::Colors::RICH_YELLOW};
        std::function<void()> _onClick;
        ImVec2 _size;

    public:
        MemoryTile(std::string const &frontImage, std::function<void()> const &onClick, ImVec2 const &size);

        void render() override;

        void flip();

        void reset();

        bool isFlipped() const;

        void setBackColor(ImVec4 color);

        ImVec4 getBackColor() const;

    };

} // namespace memory

