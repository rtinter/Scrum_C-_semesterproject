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

    /**
     * @brief The StressButton class manages the behavior of a button that appears randomly in the game.
     * The button must be clicked within a certain timeframe and keeps track of click statistics.
     */
    class StressButton {
    public:
        /**
         * @brief Constructor for StressButton.
         */
        StressButton();

        /**
         * @brief Updates the state of the stress button, handling visibility and timing.
         */
        void update();

        /**
         * @brief Renders the stress button.
         */
        void render();

        /**
         * @brief Spawns the stress button at a random position not overlapping with memory tiles.
         */
        void spawn();

        /**
         * @brief Resets the stress button state and timing.
         */
        void reset();

        /**
         * @brief Sets the data for the memory tiles and their size.
         * @param tiles Vector of shared pointers to MemoryTile objects.
         * @param tileSize Size of each memory tile.
         */
        void setTileData(std::vector<std::shared_ptr<MemoryTile>> const &tiles, ImVec2 const &tileSize);

        /**
         * @brief Gets the count of successful clicks on the stress button.
         * @return Number of times the stress button was clicked.
         */
        int getClickCount() const;

        /**
         * @brief Gets the total count of stress button spawns.
         * @return Number of times the stress button appeared.
         */
        int getTotalCount() const;

    private:
        ImVec2 _stressButtonPosition{0.0f, 0.0f};
        ImVec2 _stressButtonSize{75.0f, 75.0f};
        bool _visible{false};

        std::chrono::steady_clock::time_point _spawnTime;
        std::chrono::steady_clock::time_point _disappearTime;
        std::chrono::seconds _nextSpawnInterval;

        int _clickCount{0};
        int _totalCount{0};
        bool _clicked{false};

        std::vector<std::shared_ptr<MemoryTile>> _tiles;
        ImVec2 _tileSize;

        /**
         * @brief Updates the interval for the next spawn of the stress button.
         */
        void updateNextSpawnInterval();
    };

} // namespace memory

#endif // STRESS_BUTTON_HPP
