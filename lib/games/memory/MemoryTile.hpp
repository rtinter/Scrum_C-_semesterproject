#ifndef MEMORYTILE_HPP
#define MEMORYTILE_HPP

#include "Tile.hpp"
#include <string>
#include <functional>
#include <imgui.h>
#include <Colors.hpp>
#include <SFML/Graphics.hpp>

namespace memory {

    class MemoryTile : public ui_elements::Tile {
    private:
        bool _isFaceUp{false};
        sf::Texture _frontTexture;
        ImVec4 _backColor{commons::ColorTheme::PRIMARY_COLOR};
        std::function<void()> _onClick;
        ImVec2 _size;
        int _index;

    public:
        MemoryTile(sf::Texture const &frontTexture, std::function<void()> const &onClick, ImVec2 const &size, int index);

        void render() override;

        void flip();

        void reset();

        bool isFaceUp() const;

        void setBackColor(ImVec4 color); //unused

        ImVec4 getBackColor() const; //unused

        int getIndex() const; // Add getter for index
    };

} // namespace memory

#endif //MEMORYTILE_HPP