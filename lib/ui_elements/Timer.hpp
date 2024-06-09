#include "UiElement.hpp"
#include <string>
#include <functional>
#include <imgui.h>
#include <chrono>

#pragma once

namespace ui_elements {
    /**
     * @brief A timer that counts down from a given time.
     */
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

        /**
         * @brief Sets the timer to a highlighted state for a given amount of time.
         * @param seconds
         */
        void setHighlighted(int seconds);

        /**
         * @brief Returns the seconds left on the timer.
         * @return int
         */
        int getSeconds() const;

        /**
         * @brief Returns the minutes left on the timer.
         * @return int
         */
        int getMinutes() const;

        /**
         * @brief Expires the timer.
         */
        void expire();

        /**
         * @brief Checks if the timer is expired.
         */
        void checkExpired();

    public:
        // Constructor
        Timer() = delete;
        explicit Timer(std::string const &windowName, int const &timeInSeconds);

        /**
         * @brief Renders the timer with the current time left.
         */
        void render() override;

        /**
         * @brief Returns the total seconds left on the timer.
         * @return int
         */
        int getSecondsLeft() const;

        /**
         * @brief Returns if the timer is in the running state.
         * @return bool
         */
        bool isRunning() const;

        /**
         * @brief Returns if the timer is in the expired state.
         * @return bool
         */
        bool isExpired() const;

        /**
         * @brief Returns if the timer is in the expired state now. Only returns true once.
         * @return bool
         */
        bool isExpiredNow();

        /**
         * @brief Returns if the timer is in the highlighted state.
         * @return bool
         */
        bool isHighlighted() const;

        /**
         * @brief Starts the timer.
         */
        void start();

        /**
         * @brief Resets the timer to the initial time.
         */
        void reset();

        /**
         * @brief Reduces the time on the timer by a given amount of seconds. Sets it highlighted for 1 second.
         * @param seconds
         */
        void reduceTime(int seconds);
    };

}
