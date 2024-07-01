#pragma once

#include <string>

namespace commons {
    /**
     * @brief Static class that provides window configurations.
     */
    class WindowConfig {
    public:
        static const int WINDOW_WIDTH;
        static const int WINDOW_HEIGHT;
        static const std::string TILE;
        static const int FRAME_RATE;
    };
}
