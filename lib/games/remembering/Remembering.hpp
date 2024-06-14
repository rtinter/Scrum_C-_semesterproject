#pragma once

#include <Colors.hpp>
#include <Game.hpp>
#include <imgui.h>
#include <map>
#include "Timer.hpp"

#include "SFML/System/Clock.hpp"

namespace games {
    /******************************************************
    KOMMENTAR FÜR DAS SPIEL
    **************************************************+***/

    class Remembering : public abstract_game::Game {

        std::string _userTextBuffer;
        sf::Clock _colorClock;
        bool showText{true};
        bool _showContinueButton{false};
        bool submitted{false};
        int score{0};
        static std::string _endBoxTitleString;
        static std::string _endBoxTextString;
        ui_elements::Timer _timer{"Remembering Game", 5};
        static std::vector<int> selectedAnswers;

        std::string text = "Am 12. Juni 2024, um etwa 14:30 Uhr, saß ich im Café \"Kaffeekränzchen\" in der Hauptstraße \n"
                           "23. Plötzlich hörte ich ein lautes Geräusch von zerbrechendem Glas. Eine Person in einem \n"
                           "schwarzen Kapuzenpullover und blauen Jeans sprang aus dem Fenster des Juweliergeschäfts \"Goldglanz\" \n"
                           "gegenüber. Die Person, etwa 1,80 Meter groß und athletisch, trug eine schwarze Maske und eine \n"
                           "große Sporttasche. Er rannte in Richtung Stadtpark.\n"
                           "\n"
                           "Zwei Minuten später kam die Polizei, sicherte den Bereich und sammelte Zeugenaussagen.\n"
                           "Ein Polizist namens Müller nahm meine Beobachtungen auf. Die Eigentümerin des Juweliergeschäfts berichtete, dass mehrere teure Schmuckstücke,\n"
                           "darunter ein Diamantarmband im Wert von 10.000 Euro und eine Rolex-Uhr im Wert von 15.000 Euro, gestohlen wurden.\n"
                           "Ein weiterer Zeuge, Herr Klaus Becker, sah den Täter in ein schwarzes Audi A4 mit dem Kennzeichen B-AB 1234 einsteigen.\n"
                           "Eine zweite Person wartete im Auto.\n";

        struct Question {
            std::string question;
            std::vector<std::string> answers;
            int correctAnswerIndex;
        };
        std::vector<Question> questions;

    public:

        explicit Remembering();

        void render() override;

        void renderGame() override;

        void start() override;

        void stop() override;

        void reset() override;

        void updateStatistics() override;

        std::string getText() const;

        void displayCenteredText(std::string const &text) const;

        void initializeQuestionsAndAnswers();

        std::string displayEvaluation(int const &score, int const &size) const;

        void renderQuestion(int index, const Question &q, int &selectedAnswer);

        void setStyles();

        void renderSubmitButtons();

    };
}
