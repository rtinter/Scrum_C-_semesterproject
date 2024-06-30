#include "Timer.hpp"

#include <Fonts.hpp>
#include <sstream>
#include <iomanip>
#include <Window.hpp>


namespace ui_elements {

    // Konstruktor
    Timer::Timer(std::string const &windowName, int const &timeInSeconds)
            : _windowName(windowName), _initTimerTimeInSeconds(timeInSeconds),
              _currentTimerTimeInSeconds(timeInSeconds) {
    }

    // private methods
    void Timer::setHighlighted(int seconds){
        _highlightUntil = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
        _highlighted = true;
    }

    int Timer::getSecondsLeft() const {

        // return value if timer is not running (static value)
        if (!isRunning()) {
            if (isExpired()) {
                return 0;
            }
            return _initTimerTimeInSeconds;
        }

        // return value if timer is running (dynamic value)
        auto now {std::chrono::steady_clock::now()};
        auto duration {std::chrono::duration_cast<std::chrono::seconds>
                (now - _startPoint).count()};
        return _currentTimerTimeInSeconds - duration;
    }

    int Timer::getSeconds() const {
        if (getSecondsLeft() > 0) {
            return getSecondsLeft() % 60;
        }
        return 0;
    }

    int Timer::getMinutes() const {
        if (getSecondsLeft() > 0) { // Division durch 0 verhindern
            return getSecondsLeft() / 60;
        }
        return 0;
    }

    void Timer::expire() {
        _running = false;
        _expired = true;
        _expiredNow = true;
    }

    void Timer::checkExpired() {

        // check if timer is expired
        if (getSecondsLeft() <= 0 && isRunning()) {
            expire();
        }

        if(isHighlighted() && std::chrono::steady_clock::now() > _highlightUntil){
            _highlighted = false;
        }
    }

    // public methods
    void Timer::render() {

        // check if timer is expired
        checkExpired();

        ui_elements::Window(_windowName).render([this]() {

            if(isHighlighted()){
                ImGui::PushFont(commons::Fonts::_header1);
            }
            else {
                ImGui::PushFont(commons::Fonts::_header2);
            }

            // Create the string for the timer
            std::stringstream ss;
            ss << getMinutes() << ":" << std::setw(2) << std::setfill('0') << getSeconds();
            std::string text {ss.str()};

            ImGui::Dummy(ImVec2(this->_width, this->_height));

            // Get the position and size of the dummy
            ImVec2 pos {ImGui::GetItemRectMin()};
            ImVec2 textPos {ImVec2(
                    pos.x + ((this->_width - ImGui::CalcTextSize(text.c_str()).x) * 0.5f),
                    pos.y + ((this->_height - ImGui::CalcTextSize(text.c_str()).y) * 0.5f)
            )};

            ImDrawList &drawList {(*ImGui::GetWindowDrawList())};

            ImU32 rectangle {IM_COL32(255, 0, 0, 255)};
            ImU32 textColor {IM_COL32(255, 255, 255, 255)};
            float rounding {25.f};

            drawList.AddRectFilled(pos, ImVec2(pos.x + this->_width, pos.y + this->_height), rectangle, rounding);

            // Draw the text over the rectangle
            drawList.AddText(textPos, textColor, text.c_str());

            ImGui::PopFont();
        });
    }

    bool Timer::isRunning() const {
        return _running;
    }

    bool Timer::isExpired() const {
        return _expired;
    }

    bool Timer::isExpiredNow() {
        if(_expiredNow){
            _expiredNow = false;
            return true;
        }
        return false;
    }

    bool Timer::isHighlighted() const {
        return _highlighted;
    }

    void Timer::start() {

        // ignore if timer is already running
        if (isRunning()) {
            return;
        }

        // reset timer if expired before start again
        if (isExpired()) {
            reset();
        }

        _running = true;
        _startPoint = std::chrono::steady_clock::now();
    }

    void Timer::reset() {
        _currentTimerTimeInSeconds = _initTimerTimeInSeconds;
        _running = false;
        _expired = false;
        _expiredNow = false; // if the timer got expired right now
    }

    void Timer::reduceTime(int seconds) {

        if (getSecondsLeft() <= seconds) {
            expire();
        } else {
            _currentTimerTimeInSeconds -= seconds;
            setHighlighted(1);
        }
    }

    void Timer::resetWithNewTime(int newTimeInSeconds) {
        _currentTimerTimeInSeconds = newTimeInSeconds;
        _running = false;
        _expired = false;
        _expiredNow = false;
        _startPoint = std::chrono::steady_clock::now(); // Update the start point
    }

}
