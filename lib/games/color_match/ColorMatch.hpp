#ifndef ATHENA_COLORMATCH_H
#define ATHENA_COLORMATCH_H

#include <string>
#include <random>
#include <iostream>
#include "Game.hpp"
#include "Colors.hpp"

namespace color_match {
    class ColorMatch : public Game {

        std::string _gameDescription {
                "Unser Spiel 'Farb Wort Test' zielt darauf ab, die kognitive Flexibilität zu testen,\n"
                "eine Schlüsselkompetenz für Polizei- und Feuerwehranwärter. Dabei werden Farben als Wörter angezeigt,\n"
                "wobei die Schriftfarbe von der Bedeutung des Wortes abweicht. Der User muss schnell erkennen,\n"
                "wenn das Wort und die Schriftfarbe übereinstimmen, und daraufhin klicken.\n"
                "Durch die fortlaufende Anzeige von richtigen und falschen Antworten sowie\n"
                "eine Streak-Anzeige wird die kognitive Leistung des Users bewertet.\n"
                "Die schnelle Anpassung an unerwartete Situationen und die Fähigkeit,\n"
                "zwischen verschiedenen Reizen zu unterscheiden, sind wesentliche Fähigkeiten\n"
                "für den Einsatz von Polizei- und Feuerwehrkräften."};
        std::string _gameRules {"Auf dem Bildschirm werden zuerst Wörter in unterschiedlicher Farbe angezeigt.\n"
                "Diese sind in Reihenfolge anhand des Wortes nicht der Farbe zuzuordnen.\n"
                "Anschließend gibt es eine ähnliche Aufgabe nur muss man nun die Farbe des Wortes den Wörter unterhalb zuordnen\n"
                };
        std::string _gameControls { "Linke Maustaste: Klicken der richtigen Antworten in der richting Reihenfolge"};
        std::string const _NAME{"Farb Wort Test"};
        bool isTimeForNewRandomColors = true;
        int numberOfRandomColors = 3;
        int indexOfCurrentColor;
        int numberOfCorrectClicksInTotal = 0;
        int numberOfCorrectClicksSinceLastError = 0;

        std::vector<std::string> const _AVAILABLE_COLORS_TEXT = {"rot", "blau", "gelb", "lila", "grün"};
        std::vector<ImVec4> const _AVAILABLE_COLORS_IMVEC4 = {commons::Colors::RED, commons::Colors::BLUE,
                                                              commons::Colors::YELLOW, commons::Colors::PURPLE,
                                                              commons::Colors::GREEN};
        std::vector<std::string> randomColorsText;
        std::vector<ImVec4> randomColorsImVec4;
        std::array<std::string, 3> clickedColors;

        void start() override;

        void reset() override;
        // void updateStatistics() override;

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
        void render();


        void displayColorButtons();
    };

    void createText();
}

#endif //ATHENA_COLORMATCH_H
