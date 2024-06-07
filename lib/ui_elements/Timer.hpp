#include "UiElement.hpp"
#include <string>
#include <functional>
#include <imgui.h>
#include <chrono>

#pragma once

namespace ui_elements {

    class Timer : public UiElement {

        const float _height{80};
        const float _width{200};
        const std::string _windowName;

        bool _expired {false};
        bool _expiredNow {false};
        bool _running {false};

        int const _initTimerTimeInSeconds;
        int _currentTimerTimeInSeconds{0};

        std::chrono::steady_clock::time_point _startPoint;

        bool _highlighted {false};
        std::chrono::steady_clock::time_point _highlightUntil;

        // Methods
        void setHighlighted(int seconds);

        int getSeconds() const;
        int getMinutes() const;

        void expire();
        void checkExpired();

    public:
        // Constructors
        Timer() = delete;
        explicit Timer(std::string const &windowName, int const &timeInSeconds);

        // Render method
        void render() override;

        // Methods
        int getSecondsLeft() const;
        bool isRunning() const;
        bool isExpired() const;
        bool isExpiredNow() const;
        bool isHighlighted() const;
        void start();
        void reset();
        void reduceTime(int seconds);
    };

}
