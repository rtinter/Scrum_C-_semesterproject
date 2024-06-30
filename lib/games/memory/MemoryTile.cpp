#include "MemoryTile.hpp"
#include <imgui.h>
#include <SFML/Graphics/Texture.hpp>

namespace memory {


    MemoryTile::MemoryTile(sf::Texture const &frontTexture, std::function<void()> const &onClick, ImVec2 const &size,
                           int index)
            : Tile("", "", "", commons::ColorTheme::PRIMARY_COLOR, onClick), _frontTexture(frontTexture),
              _onClick(onClick), _size(size), _index(index) {}

    void MemoryTile::render() {
        if (_isFaceUp) {
            // Render the front of the tile using the texture.
            // The texture's native handle is cast to a void pointer as required by ImGui::Image.
            ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(_frontTexture.getNativeHandle())), _size);
        } else {
            ImGui::PushStyleColor(ImGuiCol_Button, _backColor);
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 1)); // Black border
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);   // Border size

            // Render the back of the tile as a button
            ImGui::Button(" ", _size);

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
        }

        // Check if the rendered item (tile) was clicked
        if (ImGui::IsItemClicked()) {
            if (_onClick) {
                _onClick();
            }
        }
    }

    void MemoryTile::flip() {
        _isFaceUp = !_isFaceUp;
    }

    void MemoryTile::reset() {
        _isFaceUp = false;
    }

    bool MemoryTile::isFaceUp() const {
        return _isFaceUp;
    }

    int MemoryTile::getIndex() const {
        return _index;
    }
} // namespace memory