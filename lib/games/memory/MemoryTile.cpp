#include "MemoryTile.hpp"
#include <imgui.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace memory {


    MemoryTile::MemoryTile(sf::Texture const &frontTexture, std::function<void()> const &onClick, ImVec2 const &size, int index)
            : Tile("", "", "", onClick), _frontTexture(frontTexture), _onClick(onClick), _size(size), _index(index) {}

    void MemoryTile::render() {
        if (_isFlipped) {
            ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(_frontTexture.getNativeHandle())), _size);
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, _backColor);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 1)); // Black border
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);   // Border size

            ImGui::Button(" ", _size);

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
        }

        if (ImGui::IsItemClicked()) {
            if (_onClick) {
                _onClick();
            }
        }
    }

    void MemoryTile::flip() {
        _isFlipped = !_isFlipped;
    }

    void MemoryTile::reset() {
        _isFlipped = false;
    }

    bool MemoryTile::isFlipped() const {
        return _isFlipped;
    }

    void MemoryTile::setBackColor(ImVec4 color) { //unused
        _backColor = color;
    }

    ImVec4 MemoryTile::getBackColor() const { //unused
        return _backColor;
    }

    int MemoryTile::getIndex() const {
        return _index;
    }
} // namespace memory