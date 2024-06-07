#include "Timer.hpp"
#include "../commons/Fonts.hpp"
#include "Window.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

#pragma once

namespace ui_elements {

    // Konstruktor
    Timer::Timer(std::string const &windowName, int const &timeInSeconds)
            : _windowName(windowName), _initTimerTimeInSeconds(timeInSeconds), _currentTimerTimeInSeconds(timeInSeconds) {
    }

    // private methods
    void Timer::setBlinking(int times){
        std::cout << "Blinking " << times << " times!" << std::endl;
    }

    int Timer::getDifferenceInSeconds() const {

        // return value if timer is not running (static value)
        if(!isRunning()){
            if(isExpired()){
                return 0;
            } else {
                return _initTimerTimeInSeconds;
            }
        }

        // return value if timer is running (dynamic value)
        else {
            auto now = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>
                    (now - _startPoint).count();
            return _currentTimerTimeInSeconds - duration;
        }
    }

    int Timer::getSeconds() const {
        if(getDifferenceInSeconds() > 0){
            return getDifferenceInSeconds() % 60;
        }
        else {
            return 0;
        }
    }

    int Timer::getMinutes() const {
        if(getDifferenceInSeconds() > 0){ // Division durch 0 verhindern
            return getDifferenceInSeconds() / 60;
        }
        else {
            return 0;
        }
    }

    void Timer::expire() {
        _running = false;
        _expired = true;
        _expiredNow = true;
    }

    void Timer::checkExpired(){

        // let expiredNow only be true once
        if(isExpired() && isExpiredNow()){
            _expiredNow = false;
        }

        // check if timer is expired
        if(getDifferenceInSeconds() <= 0 && isRunning()){
            expire();
        }
    }

    // public methods
    void Timer::render() {

        ui_elements::Window(_windowName).render([this]() {

            ImGui::PushFont(commons::Fonts::_header2);

            // Create the string for the timer
            std::stringstream ss;
            ss << getMinutes() << ":" << std::setw(2) << std::setfill('0') << getSeconds();
            std::string text = ss.str();

            ImGui::Dummy(ImVec2(this->_width, this->_height));

            // Get the position and size of the dummy
            ImVec2 pos = ImGui::GetItemRectMin();
            ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
            ImVec2 textPos = ImVec2(
                    pos.x + (this->_width - textSize.x) * 0.5f,
                    pos.y + (this->_height - textSize.y) * 0.5f
            );

            ImDrawList* drawList = ImGui::GetWindowDrawList();

            ImU32 rectangle = IM_COL32(255, 0, 0, 255);
            ImU32 textColor = IM_COL32(255, 255, 255, 255);
            float rounding = 25.f;

            drawList->AddRectFilled(pos, ImVec2(pos.x + this->_width, pos.y + this->_height), rectangle, rounding);

            // Draw the text over the rectangle
            drawList->AddText(textPos, textColor, text.c_str());

            ImGui::PopFont();

            // check if timer is expired
            checkExpired();
        });
    }

    bool Timer::isRunning() const {
        return _running;
    }

    bool Timer::isExpired() const {
        return _expired;
    }

    bool Timer::isExpiredNow() const {
        return _expiredNow;
    }

    void Timer::start() {

        // ignore if timer is already running
        if(isRunning()){
            return;
        }

        // reset timer if expired before start again
        if(isExpired()){
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

    void Timer::reduceTime(int seconds){

        if(getDifferenceInSeconds() <= seconds){
            expire();
        }
        else{
            _currentTimerTimeInSeconds -= seconds;
            setBlinking(3);
        }
    }

}