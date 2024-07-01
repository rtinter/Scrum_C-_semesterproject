#include "StressButton.hpp"
#include "MemoryTile.hpp"
#include <imgui.h>
#include <random>

namespace memory {

    StressButton::StressButton() = default;

    void StressButton::update() {
        if (!_visible) {
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - _disappearTime).count() >= 10) {
                spawn();
            }
        } else {
            auto now = std::chrono::steady_clock::now();
            if (now >= _disappearTime) {
                _visible = false;
            }
        }
    }

    void StressButton::render() {
        if (_visible) {
            ImGui::SetCursorPos(_position);
            ImGui::PushStyleColor(ImGuiCol_Button, _clickCount > 0 ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1));
            if (ImGui::Button("Stress", _size)) {
                _clickCount++;
                _visible = true; // Keep the button visible until disappear time
            }
            ImGui::PopStyleColor();
        }
    }

    void StressButton::spawn() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> disX(0.0f, ImGui::GetWindowWidth() - _size.x);
        std::uniform_real_distribution<float> disY(0.0f, ImGui::GetWindowHeight() - _size.y);

        bool validPosition = false;

        while (!validPosition) {
            _position = {disX(gen), disY(gen)};
            validPosition = !isOverlappingWithTiles(_position);
        }

        _visible = true;
        _spawnTime = std::chrono::steady_clock::now();
        _disappearTime = _spawnTime + std::chrono::seconds(2); // Stays visible for 2 seconds
        _totalCount++;
    }

    bool StressButton::isOverlappingWithTiles(ImVec2 const &position) {
        for (const auto &tile : _tiles) {
            ImVec2 tilePos = tile->getPosition();
            if (position.x >= tilePos.x && position.x <= tilePos.x + _tileSize.x &&
                position.y >= tilePos.y && position.y <= tilePos.y + _tileSize.y) {
                return true;
            }
        }
        return false;
    }

    void StressButton::setTileData(std::vector<std::shared_ptr<MemoryTile>> const &tiles, ImVec2 const &tileSize) {
        _tiles = tiles;
        _tileSize = tileSize;
    }

    bool StressButton::isVisible() const {
        return _visible;
    }

    int StressButton::getClickCount() const {
        return _clickCount;
    }

    int StressButton::getTotalCount() const {
        return _totalCount;
    }

    float StressButton::getSuccessRate() const {
        if (_totalCount == 0) return 0.0f;
        return static_cast<float>(_clickCount) / _totalCount * 100.0f;
    }

} // namespace memory
