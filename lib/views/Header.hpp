#pragma once

#include <functional>
#include <string>


namespace views {
    /**
     * The Header is displayed above the home page and the game pages.
     * In the center of the header is the title “Athena”,
     * on the right there is a button to access the statistics.
     * The text on the left shows where you are currently located (Home, Game X, ...)
     */
    class Header {
        std::string _leftText;
        std::string _centerText;
        std::string _rightButtonText;
        std::function<void()> _buttonClickCallback;

        static constexpr float HEADER_HEIGHT{55.0f};
        static constexpr float SIDE_MARGIN{30.0f};
        static constexpr float TOP_MARGIN{10.0f};

    public:
        // Konstruktor
        explicit Header(std::string const &left, std::string const &right, std::function<void()> const &callback);

        // Render-Methode
        void render() const;
    };
} // views
