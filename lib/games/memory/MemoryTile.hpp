#ifndef MEMORYTILE_HPP
#define MEMORYTILE_HPP

#include "Tile.hpp"
#include <string>
#include <functional>
#include <imgui.h>
#include <Colors.hpp>
#include <SFML/Graphics.hpp>

namespace memory {
    /**
     * @brief MemoryTile class. Represents a tile in the Memory game.
     */
    class MemoryTile : public ui_elements::Tile {
    private:
        sf::Texture _frontTexture;
        ImVec4 _backColor{commons::ColorTheme::PRIMARY_COLOR};
        std::function<void()> _onClick;
        ImVec2 _size;
        int _index;
        bool _isFaceUp{false};

    public:
        MemoryTile(sf::Texture const &frontTexture, std::function<void()> const &onClick, ImVec2 const &size, int index);
        void render() override;
        void flip();
        void reset();
        bool isFaceUp() const;
        int getIndex() const;
    };

} // namespace memory

#endif //MEMORYTILE_HPP