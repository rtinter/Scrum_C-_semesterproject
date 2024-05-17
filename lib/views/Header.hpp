#include <string>
#include <imgui.h>
#include <functional>


class Header {
    std::string leftText;
    std::string centerText;
    std::string rightButtonText;
    std::function<void()> buttonClickCallback;

public:
    // Konstruktor
    Header(const std::string& left, const std::string& right, std::function<void()> callback);

    // Render-Methode
    void render();
};