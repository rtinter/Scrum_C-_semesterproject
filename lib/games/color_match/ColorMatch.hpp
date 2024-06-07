#ifndef ATHENA_COLORMATCH_H
#define ATHENA_COLORMATCH_H

#include <string>
#include <random>
#include <iostream>
#include "Game.hpp"
#include "Colors.hpp"

namespace games {
    class ColorMatch : public Game {
        std::string const _NAME{"Farb-Wort-Spiel"};
        bool isTimeForNewRandomColors = true;
        int numberOfRandomColors = 3;
        int indexOfCurrentColor;
        int numberOfCorrectClicksInTotal = 0;
        int numberOfCorrectClicksSinceLastError = 0;

        std::vector<std::string> const _AVAILABLE_COLORS_TEXT{"rot", "blau", "gelb", "lila", "grün"};
        std::vector<ImVec4> const _AVAILABLE_COLORS_IMVEC4{commons::Colors::RED, commons::Colors::BLUE,
                                                           commons::Colors::YELLOW, commons::Colors::PURPLE,
                                                           commons::Colors::GREEN};
        std::vector<std::string> randomColorsText;
        std::vector<ImVec4> randomColorsImVec4;
        std::array<std::string, 3> clickedColors;


        template<typename T>
        T getRandomElement(const std::vector<T> &v) {
            std::random_device rd;      // Zufallszahlengenerator initialisieren
            std::mt19937 gen(rd());     // Mersenne Twister mit rd seeden
            std::uniform_int_distribution<> dis(0, _AVAILABLE_COLORS_TEXT.size() - 1); // Gleichverteilung
            return v[dis(gen)];         // Zugriff auf zufälliges Element
        }

        void displayRandomColors();

        void pickRandomColorsText();

        void pickRandomColorsImVec4();

    public:
        void start() override;

        void reset() override;

        // void updateStatistics() override;
        std::string getName() const override;

        void render();

        void displayColorButtons();
    };

    void createText();
}

#endif //ATHENA_COLORMATCH_H
