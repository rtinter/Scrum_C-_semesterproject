#include <string>
#include <imgui.h>
#include <functional>

#pragma once

class Header {
    std::string _leftText;
    std::string _centerText;
    std::string _rightButtonText;
    std::function<void()> _buttonClickCallback;

    static constexpr float kHEADER_HEIGHT = 300.0f;
    static constexpr float kSIDE_MARGIN = 30.0f;
    static constexpr float kTOP_MARGIN = 10.0f;
    static constexpr float kBOTTOM_MARGIN = 10.0f;

public:
    // Konstruktor
    Header(std::string left, std::string right, std::function<void()> callback);

    // Render-Methode
    void render();
};