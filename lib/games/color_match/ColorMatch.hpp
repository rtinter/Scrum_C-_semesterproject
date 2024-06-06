#ifndef ATHENA_COLORMATCH_H
#define ATHENA_COLORMATCH_H

#include <string>
#include <random>
#include <jmorecfg.h>
#include <iostream>
#include "Game.hpp"
#include "Colors.hpp"

namespace color_match {
    class ColorMatch : public Game {
        std::string const _NAME{"Reaction"};
        boolean isTimeForNewColors = true;
        int numberOfColorsToChoose = 3;

        std::vector<const char *> const _AVAILABLE_COLORS_TEXT = {"rot", "blau", "gelb", "lila", "grün"};
        std::vector<ImVec4> const _AVAILABLE_COLORS_IMVEC4 = {commons::Colors::RED, commons::Colors::BLUE,
                                                              commons::Colors::YELLOW, commons::Colors::PURPLE,
                                                              commons::Colors::GREEN};
        std::vector<const char *> chosenColorsText;
        std::vector<ImVec4> chosenColorsImVec4;

        void start() override;

        void reset() override;
        // void updateStatistics() override;

        template<typename T>
        T getRandomElement(const std::vector<T> &v) {
            std::random_device rd;      // Zufallszahlengenerator initialisieren
            std::mt19937 gen(rd());     // Mersenne Twister mit rd seeden
            std::uniform_int_distribution<> dis(0, _AVAILABLE_COLORS_TEXT.size()); // Gleichverteilung
            return v[dis(gen)];         // Zugriff auf zufälliges Element
        }

        void displayChosenColors();

        void chooseColorsText();

        void chooseColorsImVec4();

    public:
        void render();


    };

    void createText();
}

#endif //ATHENA_COLORMATCH_H
