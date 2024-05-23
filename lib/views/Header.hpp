#include <string>
#include <imgui.h>
#include <functional>

#pragma once

class Header {
    std::string leftText;
    std::string centerText;
    std::string rightButtonText;
    std::function<void()> buttonClickCallback;

    static constexpr float headerHeight = 300.0f;
    static constexpr float sideMargin = 30.0f;
    static constexpr float topMargin = 10.0f;

public:
    // Konstruktor
    Header(std::string left, std::string right, std::function<void()> callback);

    // Render-Methode
    void render();
};