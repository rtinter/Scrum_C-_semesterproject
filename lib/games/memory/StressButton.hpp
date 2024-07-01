#ifndef STRESS_BUTTON_HPP
#define STRESS_BUTTON_HPP

#include <imgui.h>
#include <chrono>
#include <functional>
#include <memory>
#include "UiElement.hpp"
#include "MemoryTile.hpp"

namespace memory {

    class MemoryTile; // Forward declaration

    class StressButton {
    public:
        StressButton();

        void update();
        void render();
        void spawn();

        void setTileData(std::vector<std::shared_ptr<MemoryTile>> const &tiles, ImVec2 const &tileSize);

        bool isVisible() const;
        int getClickCount() const;
        int getTotalCount() const;
        float getSuccessRate() const;

    private:
        ImVec2 _position{0.0f, 0.0f};
        ImVec2 _size{50.0f, 50.0f};
        bool _visible{false};
        std::chrono::steady_clock::time_point _spawnTime;
        std::chrono::steady_clock::time_point _disappearTime;
        int _clickCount{0};
        int _totalCount{0};

        std::vector<std::shared_ptr<MemoryTile>> _tiles;
        ImVec2 _tileSize;

        bool isOverlappingWithTiles(ImVec2 const &position);
    };

} // namespace memory

#endif // STRESS_BUTTON_HPP
