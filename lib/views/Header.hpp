#include <string>
#include <imgui.h>
#include <functional>

#pragma once

/***********************************************************************************
 * The Header is displayed above the home page and the game pages.
 * In the center of the header is the title “Athena”,
 * on the right there is a button to access the statistics.
 * The text on the left shows where you are currently located (Home, Game X, ...)
 ***********************************************************************************/
class Header {
    std::string _leftText;
    std::string _centerText;
    std::string _rightButtonText;
    std::function<void()> _buttonClickCallback;

    static constexpr float kHEADER_HEIGHT = 100.0f;
    static constexpr float kSIDE_MARGIN = 30.0f;
    static constexpr float kTOP_MARGIN = 10.0f;

public:
    // Konstruktor
    Header(std::string left, std::string right, std::function<void()> callback);

    // Render-Methode
    void render();

    // Getter und Setter für den linken Text
    const std::string& getLeftText() const;
    void setLeftText(const std::string& leftText);

    // Getter und Setter für den rechten Button-Text
    const std::string& getRightButtonText() const;
    void setRightButtonText(const std::string& rightButtonText);

    // Getter und Setter für die Button-Klick-Callback-Funktion
    const std::function<void()>& getButtonClickCallback() const;
    void setButtonClickCallback(const std::function<void()>& callback);

};