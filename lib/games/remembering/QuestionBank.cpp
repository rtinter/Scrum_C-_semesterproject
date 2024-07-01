#include "QuestionBank.hpp"

#include <random>

namespace remembering {
    QuestionBank::QuestionBank() {
        _questionSets = {
            {
                .text = "Am 12. Juni 2024, um etwa 14:30 Uhr, saß ich im Café Kaffeekränzchen in der Hauptstraße 23. \n"
                "Plötzlich hörte ich ein lautes Geräusch von zerbrechendem Glas. Eine Person in einem \n"
                "schwarzen Kapuzenpullover und blauen Jeans sprang aus dem Fenster des Juweliergeschäfts \"Goldglanz\" \n"
                "gegenüber. Die Person, etwa 1,80 Meter groß und athletisch, trug eine schwarze Maske und eine \n"
                "große Sporttasche. Er rannte in Richtung Stadtpark.\n"
                "Zwei Minuten später kam die Polizei, sicherte den Bereich und sammelte Zeugenaussagen.\n"
                "Ein Polizist namens Müller nahm meine Beobachtungen auf. Die Eigentümerin des Juweliergeschäfts berichtete, dass mehrere teure Schmuckstücke,\n"
                "darunter ein Diamantarmband im Wert von 10.000 Euro und eine Rolex-Uhr im Wert von 15.000 Euro, gestohlen wurden.\n"
                "Ein weiterer Zeuge, Herr Klaus Becker, sah den Täter in einem schwarzen Audi A4 mit dem Kennzeichen KI-AB 1234 einsteigen.\n"
                "Eine zweite Person wartete im Auto.\n",
                .questions = {
                    {
                        .question = "In welchem Monat fand das Ereignis statt?",
                        .answers = {"Januar", "Mai", "Juni", "Dezember"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Um wie viel Uhr fand das Ereignis statt?",
                        .answers = {"13:00", "14:30", "15:00", "16:30"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welchem Café saß die Person?",
                        .answers = {"Bäckerei", "Kaffeekränzchen", "Restaurant", "Bar"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welcher Straße liegt das Café?",
                        .answers = {"Bahnhofstraße", "Hauptstraße", "Nebenstraße", "Ringstraße"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welches Geräusch hörte die Person?",
                        .answers = {"Schrei", "Sirene", "Glas", "Motor"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Was trug die Person?", .answers = {"Kapuzenpullover", "Anzug", "T-Shirt", "Hemd"},
                        .correctAnswerIndex = 0
                    },
                    {
                        .question = "Welche Farbe hatte die Jeans der Person?",
                        .answers = {"schwarz", "rot", "blau", "weiß"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Wie groß war die Person?", .answers = {"1,60", "1,70", "1,80", "1,90"},
                        .correctAnswerIndex = 2
                    },
                    {
                        .question = "In welche Richtung rannte die Person?",
                        .answers = {"Bahnhof", "Stadtpark", "Marktplatz", "Kirche"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wie heißt der Polizist?", .answers = {"Schmidt", "Müller", "Weber", "Fischer"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wie viel ist das Diamantarmband wert?",
                        .answers = {"5.000", "10.000", "15.000", "20.000"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wie viel ist die Rolex-Uhr wert?",
                        .answers = {"10.000", "15.000", "20.000", "25.000"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welches Auto fuhr der Täter?",
                        .answers = {"BMW", "Mercedes", "Audi", "Volkswagen"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Welches Kennzeichen hatte das Auto?",
                        .answers = {"KI-CD 1234", "KI-AB 1234", "KI-EF 5678", "KI-GH 9012"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wartete noch jemand im Auto?", .answers = {"ja", "nein", "vergessen", "unbekannt"},
                        .correctAnswerIndex = 0
                    }
                }
            },
            {
                .text =
                "Am 25. April 2024, gegen 17:45 Uhr, ging ich durch den Stadtpark, als ich plötzlich laute Rufe hörte. \n"
                "Ein Mann, etwa 1,85 Meter groß, mit braunen Haaren und einem grünen T-Shirt, stritt heftig mit einer anderen Person. \n"
                "Der Mann schlug die andere Person und rannte dann in Richtung der Parkausgang auf der Südseite. \n"
                "Die Polizei traf zehn Minuten später ein und nahm meine Aussage auf.\n "
                "Der Mann, der geschlagen wurde, identifizierte den Angreifer als Herrn Michael Wagner. \n"
                "Ein weiterer Zeuge, Frau Anna Schmidt, sah den Täter in ein\n"
                "rotes Fahrrad steigen und in Richtung Hauptstraße fahren.\n",
                .questions = {
                    {
                        .question = "In welchem Monat fand das Ereignis statt?",
                        .answers = {"Januar", "März", "April", "Juli"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Um wie viel Uhr fand das Ereignis statt?",
                        .answers = {"16:00", "17:45", "18:30", "19:00"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wo ereignete sich der Vorfall?",
                        .answers = {"Stadtpark", "Bahnhof", "Marktplatz", "Einkaufszentrum"}, .correctAnswerIndex = 0
                    },
                    {
                        .question = "Welche Haarfarbe hatte der Täter?",
                        .answers = {"schwarz", "blond", "braun", "rot"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Welche Farbe hatte das T-Shirt des Täters?",
                        .answers = {"blau", "grün", "rot", "weiß"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welche Richtung rannte der Täter?",
                        .answers = {"Nordseite", "Südseite", "Westseite", "Ostseite"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wie lange dauerte es, bis die Polizei eintraf?",
                        .answers = {"fünf Minuten", "zehn Minuten", "zwanzig Minuten", "dreißig Minuten"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wie heißt der Angreifer?",
                        .answers = {"Thomas Müller", "Michael Wagner", "Hans Becker", "Peter Fischer"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welches Verkehrsmittel benutzte der Täter zur Flucht?",
                        .answers = {"Auto", "Fahrrad", "Motorrad", "zu Fuß"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welche Richtung fuhr der Täter nach der Flucht aus dem Park?",
                        .answers = {"Nordstraße", "Hauptstraße", "Lindenstraße", "Parkstraße"}, .correctAnswerIndex = 1
                    }
                }
            },
            {
                .text =
                "Am 8. März 2024, um circa 11:15 Uhr, befand ich mich im Supermarkt Einkaufsparadies in der Berliner Allee 5. \n"
                "Plötzlich bemerkte ich, dass ein Mann im Alter von etwa 35 Jahren, mit einer schwarzen Jacke und einer grauen Mütze,\n"
                "etwas in seine Tasche steckte und hastig zur Kasse ging. \n"
                "Als der Kassierer ihn ansprach, rannte der Mann aus dem Geschäft. \n"
                "Ich sah, wie er in einen blauen Volkswagen Passat mit dem Kennzeichen KI-CX 6789 stieg und in Richtung Autobahnauffahrt fuhr. \n"
                "Kurz darauf traf die Polizei ein und begann mit der Aufnahme von Zeugenaussagen. \n"
                "Die Kassiererin berichtete, dass der Mann eine teure Flasche Whisky im Wert von 200 Euro gestohlen hatte.\n",
                .questions = {
                    {
                        .question = "In welchem Monat fand das Ereignis statt?",
                        .answers = {"Februar", "März", "Mai", "August"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Um wie viel Uhr fand das Ereignis statt?",
                        .answers = {"10:00", "11:15", "12:30", "14:00"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welchem Supermarkt befand sich die Person?",
                        .answers = {"Supermarkt", "Einkaufsparadies", "Shoppingcenter", "Lebensmittelmarkt"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welcher Straße liegt der Supermarkt?",
                        .answers = {"Hauptstraße", "Berliner Allee", "Marktstraße", "Bahnhofstraße"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welche Farbe hatte die Jacke des Täters?",
                        .answers = {"schwarz", "blau", "grün", "rot"}, .correctAnswerIndex = 0
                    },
                    {
                        .question = "Welche Art von Kopfbedeckung trug der Täter?",
                        .answers = {"Hut", "Mütze", "Kappe", "Helm"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welches Auto fuhr der Täter?",
                        .answers = {"BMW", "Mercedes", "Volkswagen", "Audi"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Welches Kennzeichen hatte das Auto?",
                        .answers = {"KI-AB 1234", "KI-CX 6789", "KI-XY 9876", "KI-CD 4321"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welche Richtung fuhr der Täter nach dem Diebstahl?",
                        .answers = {"Stadtzentrum", "Bahnhof", "Autobahnauffahrt", "Park"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Wie viel war die gestohlene Flasche Whisky wert?",
                        .answers = {"100 Euro", "150 Euro", "200 Euro", "250 Euro"}, .correctAnswerIndex = 2
                    }
                }
            },
            {
                .text =
                "Am 19. September 2024, gegen 21:00 Uhr, saß ich im Kino Filmwelt in der Rosenstraße 12 und schaute einen Film. \n"
                "Plötzlich hörte ich Schreie aus dem Flur. Ich eilte hinaus und \n"
                "sah einen Mann mit einer weißen Maske und einem schwarzen Mantel, der einen Kinobesucher bedrohte. \n"
                "Der Mann, etwa 1,75 Meter groß, hatte eine Pistole und forderte Geld.\n"
                "Nachdem er das Geld bekommen hatte, rannte er durch den Notausgang. \n"
                "Die Polizei kam kurze Zeit später und begann mit der Untersuchung. \n"
                "Der bedrohte Kinobesucher berichtete, dass der Täter etwa 500 Euro erbeutet hatte. \n"
                "Ein weiterer Zeuge, Frau Lisa Meier, sah den Täter in einen weißen Toyota Corolla steigen und in Richtung Bahnhof fahren.\n",
                .questions = {
                    {
                        .question = "In welchem Monat fand das Ereignis statt?",
                        .answers = {"Juli", "August", "September", "Oktober"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Um wie viel Uhr fand das Ereignis statt?",
                        .answers = {"20:00", "21:00", "22:00", "23:00"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welchem Kino befand sich die Person?",
                        .answers = {"Kino", "Filmwelt", "Lichtspiele", "Filmtheater"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welcher Straße liegt das Kino?",
                        .answers = {"Hauptstraße", "Rosenstraße", "Gartenstraße", "Bahnhofstraße"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welche Farbe hatte die Maske des Täters?",
                        .answers = {"schwarz", "weiß", "rot", "blau"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welche Farbe hatte der Mantel des Täters?",
                        .answers = {"schwarz", "grau", "braun", "grün"}, .correctAnswerIndex = 0
                    },
                    {
                        .question = "Wie groß war der Täter?", .answers = {"1,60", "1,70", "1,75", "1,80"},
                        .correctAnswerIndex = 2
                    },
                    {
                        .question = "Welches Fahrzeug fuhr der Täter?",
                        .answers = {"BMW", "Mercedes", "Toyota", "Audi"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "In welche Richtung fuhr der Täter nach dem Überfall?",
                        .answers = {"Stadtpark", "Marktplatz", "Bahnhof", "Autobahnauffahrt"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Wie viel Geld erbeutete der Täter?",
                        .answers = {"300 Euro", "400 Euro", "500 Euro", "600 Euro"}, .correctAnswerIndex = 2
                    }
                }
            },
            {
                .text =
                "Am 30. Juli 2024, um circa 10:00 Uhr, war ich im Einkaufszentrum Citti-Park in der Gartenstraße 45. \n"
                "Plötzlich bemerkte ich, dass ein Mann, etwa 1,75 Meter groß,\n"
                "mit einem blauen Hemd und einer schwarzen Hose, hektisch durch die Läden ging und mehrere Produkte in seine Tasche steckte. \n"
                "Als er das Einkaufszentrum verlassen wollte, sprach ihn ein Sicherheitsmitarbeiter an.\n"
                "Der Mann rannte daraufhin weg und ich sah, wie er in einen silbernen Mercedes\n"
                "mit dem Kennzeichen KI-KL 5678 stieg und in Richtung Innenstadt fuhr. \n"
                "Die Polizei kam kurz darauf an und nahm Zeugenaussagen auf. \n"
                "Die Ladenbesitzerin berichtete, dass der Mann mehrere Elektronikartikel im Wert von 800 Euro gestohlen hatte.\n",
                .questions = {
                    {
                        .question = "In welchem Monat fand das Ereignis statt?",
                        .answers = {"Juni", "Juli", "August", "September"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Um wie viel Uhr fand das Ereignis statt?",
                        .answers = {"09:00", "10:00", "11:00", "12:00"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welchem Einkaufszentrum befand sich die Person?",
                        .answers = {"Citti-Park", "Shopping Center", "Einkaufsparadies", "Mall of City"},
                        .correctAnswerIndex = 0
                    },
                    {
                        .question = "In welcher Straße liegt das Einkaufszentrum?",
                        .answers = {"Hauptstraße", "Gartenstraße", "Berliner Allee", "Bahnhofstraße"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welche Farbe hatte das Hemd des Täters?",
                        .answers = {"blau", "rot", "grün", "schwarz"}, .correctAnswerIndex = 0
                    },
                    {
                        .question = "Welche Farbe hatte die Hose des Täters?",
                        .answers = {"schwarz", "weiß", "grau", "braun"}, .correctAnswerIndex = 0
                    },
                    {
                        .question = "Wie groß war der Täter?", .answers = {"1,60", "1,70", "1,75", "1,80"},
                        .correctAnswerIndex = 2
                    },
                    {
                        .question = "Welches Auto fuhr der Täter?",
                        .answers = {"BMW", "Mercedes", "Audi", "Volkswagen"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welches Kennzeichen hatte das Auto?",
                        .answers = {"KI-AB 1234", "KI-CD 5678", "KI-EF 9012", "KI-KL 5678"},
                        .correctAnswerIndex = 3
                    },
                    {
                        .question = "In welche Richtung fuhr der Täter nach dem Diebstahl?",
                        .answers = {"Stadtpark", "Marktplatz", "Innenstadt", "Autobahn"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Wie viel waren die gestohlenen Elektronikartikel wert?",
                        .answers = {"500 Euro", "600 Euro", "700 Euro", "800 Euro"}, .correctAnswerIndex = 3
                    }
                }
            },
            {
                .text =
                "Am 15. November 2024, gegen 18:30 Uhr, saß ich im Restaurant Gourmet Palace in der Königstraße 17 und genoss mein Abendessen. \n"
                "Plötzlich sah ich einen Mann durch das Fenster, etwa 1,90 Meter groß, mit einer roten Jacke und\n"
                "einer schwarzen Mütze, welcher eine Handtasche von einer vorbeigehenden Frau stahl. \n"
                "Der Mann rannte schnell in Richtung Flughafen. Ich alarmierte sofort die Polizei, die wenige Minuten später eintraf. \n"
                "Die bestohlene Frau berichtete, dass ihre Handtasche 300 Euro Bargeld sowie wichtige Dokumente enthielt. \n"
                "Ein weiterer Zeuge, Herr Peter Schmitz, sah den Täter in einen grünen\n"
                "Opel Corsa mit dem Kennzeichen KI-XY 3456 steigen und wegfahren.\n",
                .questions = {
                    {
                        .question = "In welchem Monat fand das Ereignis statt?",
                        .answers = {"September", "Oktober", "November", "Dezember"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Um wie viel Uhr fand das Ereignis statt?",
                        .answers = {"17:30", "18:30", "19:30", "20:30"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "In welchem Restaurant saß die Person?",
                        .answers = {"Gourmet Palace", "Feinschmecker", "Delikatessen", "Essparadies"},
                        .correctAnswerIndex = 0
                    },
                    {
                        .question = "In welcher Straße liegt das Restaurant?",
                        .answers = {"Hauptstraße", "Königstraße", "Marktstraße", "Gartenstraße"},
                        .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welche Farbe hatte die Jacke des Täters?",
                        .answers = {"blau", "rot", "grün", "schwarz"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Welche Art von Kopfbedeckung trug der Täter?",
                        .answers = {"Hut", "Mütze", "Kappe", "Helm"}, .correctAnswerIndex = 1
                    },
                    {
                        .question = "Wie groß war der Täter?", .answers = {"1,70", "1,80", "1,90", "2,00"},
                        .correctAnswerIndex = 2
                    },
                    {
                        .question = "Welches Fahrzeug fuhr der Täter?",
                        .answers = {"BMW", "Mercedes", "Opel", "Volkswagen"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Welches Kennzeichen hatte das Auto?",
                        .answers = {"KI-AB 1234", "KI-CD 5678", "KI-EF 9012", "KI-XY 3456"},
                        .correctAnswerIndex = 3
                    },
                    {
                        .question = "In welche Richtung rannte der Täter nach dem Diebstahl?",
                        .answers = {"Stadtpark", "Marktplatz", "Flughafen", "Autobahnauffahrt"}, .correctAnswerIndex = 2
                    },
                    {
                        .question = "Wie viel Bargeld befand sich in der gestohlenen Handtasche?",
                        .answers = {"200 Euro", "250 Euro", "300 Euro", "350 Euro"}, .correctAnswerIndex = 2
                    }
                }
            }
        };
    }

    // get a random question
    QuestionBank::QuestionSet const &QuestionBank::getRandomQuestionSet() const {
        static std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, _questionSets.size() - 1);
        return _questionSets[dis(gen)];
    }
} // remembering
