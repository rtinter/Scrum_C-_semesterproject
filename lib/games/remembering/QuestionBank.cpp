#include "QuestionBank.hpp"
#include <random>

QuestionBank::QuestionBank() {
    _questionSets = {
            {
                    "Am 12. Juni 2024, um etwa 14:30 Uhr, saß ich im Café Kaffeekränzchen in der Hauptstraße 23. \n"
                    "Plötzlich hörte ich ein lautes Geräusch von zerbrechendem Glas. Eine Person in einem \n"
                    "schwarzen Kapuzenpullover und blauen Jeans sprang aus dem Fenster des Juweliergeschäfts \"Goldglanz\" \n"
                    "gegenüber. Die Person, etwa 1,80 Meter groß und athletisch, trug eine schwarze Maske und eine \n"
                    "große Sporttasche. Er rannte in Richtung Stadtpark.\n"
                    "Zwei Minuten später kam die Polizei, sicherte den Bereich und sammelte Zeugenaussagen.\n"
                    "Ein Polizist namens Müller nahm meine Beobachtungen auf. Die Eigentümerin des Juweliergeschäfts berichtete, dass mehrere teure Schmuckstücke,\n"
                    "darunter ein Diamantarmband im Wert von 10.000 Euro und eine Rolex-Uhr im Wert von 15.000 Euro, gestohlen wurden.\n"
                    "Ein weiterer Zeuge, Herr Klaus Becker, sah den Täter in ein schwarzes Audi A4 mit dem Kennzeichen KI-AB 1234 einsteigen.\n"
                    "Eine zweite Person wartete im Auto.\n",
                    {
                            {"In welchem Monat fand das Ereignis statt?", {"Januar",    "Mai",     "Juni",      "Dezember"},  2},
                            {"Um wieviel Uhr fand das Ereignis statt?", {"13:00", "14:30", "15:00", "16:30"}, 1},
                            {"In welchem Café saß die Person?",                    {"Bäckerei",       "Kaffeekränzchen", "Restaurant",       "Bar"},          1},
                            {"In welcher Straße liegt das Café?",            {"Bahnhofstraße", "Hauptstraße",  "Nebenstraße",    "Ringstraße"},    1},
                            {"Welches Geräusch hörte die Person?",       {"Schrei",  "Sirene", "Glas", "Motor"},   2},
                            {"Was trug die Person?",                         {"Kapuzenpullover", "Anzug", "T-Shirt", "Hemd"},  0},
                            {"Welche Farbe hatte die Jeans der Person?", {"schwarz", "rot",  "blau", "weiß"}, 2},
                            {"Wie groß war die Person?",         {"1,60", "1,70",     "1,80",   "1,90"},       2},
                            {"In welche Richtung rannte die Person?",                {"Bahnhof",    "Stadtpark",  "Marktplatz", "Kirche"},           1},
                            {"Wie heißt der Polizist?",                                 {"Schmidt",   "Müller",     "Weber",      "Fischer"},          1},
                            {"Wie viel ist das Diamantarmband wert?",                       {"5.000",    "10.000",   "15.000",   "20.000"},   1},
                            {"Wie viel ist die Rolex-Uhr wert?", {"10.000", "15.000", "20.000", "25.000"}, 1},
                            {"Welches Auto fuhr der Täter?", {"BMW", "Mercedes", "Audi", "Volkswagen"}, 2},
                            {"Welches Kennzeichen hatte das Auto?", {"KI-CD 1234", "KI-AB 1234", "KI-EF 5678", "KI-GH 9012"}, 1},
                            {"Wartete noch jemand im Auto?", {"ja", "nein", "vergessen", "unbekannt"}, 0}
                    }
            },
            {
                    "Am 25. April 2024, gegen 17:45 Uhr, ging ich durch den Stadtpark, als ich plötzlich laute Rufe hörte. \n"
                    "Ein Mann, etwa 1,85 Meter groß, mit braunen Haaren und einem grünen T-Shirt, stritt heftig mit einer anderen Person. \n"
                    "Der Mann schlug die andere Person und rannte dann in Richtung der Parkausgang auf der Südseite. \n"
                    "Die Polizei traf zehn Minuten später ein und nahm meine Aussage auf.\n "
                    "Der Mann, der geschlagen wurde, identifizierte den Angreifer als Herrn Michael Wagner. \n"
                    "Ein weiterer Zeuge, Frau Anna Schmidt, sah den Täter in ein\n"
                    "rotes Fahrrad steigen und in Richtung Hauptstraße fahren.\n",
                    {
                            {"In welchem Monat fand das Ereignis statt?", {"Januar", "März", "April", "Juli"}, 2},
                            {"Um wie viel Uhr fand das Ereignis statt?", {"16:00", "17:45", "18:30", "19:00"}, 1},
                            {"Wo ereignete sich der Vorfall?", {"Stadtpark", "Bahnhof", "Marktplatz", "Einkaufszentrum"}, 0},
                            {"Welche Haarfarbe hatte der Täter?", {"schwarz", "blond", "braun", "rot"}, 2},
                            {"Welche Farbe hatte das T-Shirt des Täters?", {"blau", "grün", "rot", "weiß"}, 1},
                            {"In welche Richtung rannte der Täter?", {"Nordseite", "Südseite", "Westseite", "Ostseite"}, 1},
                            {"Wie lange dauerte es, bis die Polizei eintraf?", {"fünf Minuten", "zehn Minuten", "zwanzig Minuten", "dreißig Minuten"}, 1},
                            {"Wie heißt der Angreifer?", {"Thomas Müller", "Michael Wagner", "Hans Becker", "Peter Fischer"}, 1},
                            {"Welches Verkehrsmittel benutzte der Täter zur Flucht?", {"Auto", "Fahrrad", "Motorrad", "zu Fuß"}, 1},
                            {"In welche Richtung fuhr der Täter nach der Flucht aus dem Park?", {"Nordstraße", "Hauptstraße", "Lindenstraße", "Parkstraße"}, 1}
                    }
            },
            {
                    "Am 8. März 2024, um circa 11:15 Uhr, befand ich mich im Supermarkt Einkaufsparadies in der Berliner Allee 5. \n"
                    "Plötzlich bemerkte ich, dass ein Mann im Alter von etwa 35 Jahren, mit einer schwarzen Jacke und einer grauen Mütze,\n"
                    "etwas in seine Tasche steckte und hastig zur Kasse ging. \n"
                    "Als der Kassierer ihn ansprach, rannte der Mann aus dem Geschäft. \n"
                    "Ich sah, wie er in einen blauen Volkswagen Passat mit dem Kennzeichen KI-CX 6789 stieg und in Richtung Autobahnauffahrt fuhr. \n"
                    "Kurz darauf traf die Polizei ein und begann mit der Aufnahme von Zeugenaussagen. \n"
                    "Die Kassiererin berichtete, dass der Mann eine teure Flasche Whisky im Wert von 200 Euro gestohlen hatte.\n",
                    {
                            {"In welchem Monat fand das Ereignis statt?", {"Februar", "März", "Mai", "August"}, 1},
                            {"Um wieviel Uhr fand das Ereignis statt?", {"10:00", "11:15", "12:30", "14:00"}, 1},
                            {"In welchem Supermarkt befand sich die Person?", {"Supermarkt", "Einkaufsparadies", "Shoppingcenter", "Lebensmittelmarkt"}, 1},
                            {"In welcher Straße liegt der Supermarkt?", {"Hauptstraße", "Berliner Allee", "Marktstraße", "Bahnhofstraße"}, 1},
                            {"Welche Farbe hatte die Jacke des Täters?", {"schwarz", "blau", "grün", "rot"}, 0},
                            {"Welche Art von Kopfbedeckung trug der Täter?", {"Hut", "Mütze", "Kappe", "Helm"}, 1},
                            {"Welches Auto fuhr der Täter?", {"BMW", "Mercedes", "Volkswagen", "Audi"}, 2},
                            {"Welches Kennzeichen hatte das Auto?", {"KI-AB 1234", "KI-CX 6789", "KI-XY 9876", "KI-CD 4321"}, 1},
                            {"In welche Richtung fuhr der Täter nach dem Diebstahl?", {"Stadtzentrum", "Bahnhof", "Autobahnauffahrt", "Park"}, 2},
                            {"Wie viel war die gestohlene Flasche Whisky wert?", {"100 Euro", "150 Euro", "200 Euro", "250 Euro"}, 2}
                    }
            },
            {
                    "Am 19. September 2024, gegen 21:00 Uhr, saß ich im Kino Filmwelt in der Rosenstraße 12 und schaute einen Film. \n"
                    "Plötzlich hörte ich Schreie aus dem Flur. Ich eilte hinaus und \n"
                    "sah einen Mann mit einer weißen Maske und einem schwarzen Mantel, der einen Kinobesucher bedrohte. \n"
                    "Der Mann, etwa 1,75 Meter groß, hatte eine Pistole und forderte Geld.\n"
                    "Nachdem er das Geld bekommen hatte, rannte er durch den Notausgang. \n"
                    "Die Polizei kam kurze Zeit später und begann mit der Untersuchung. \n"
                    "Der bedrohte Kinobesucher berichtete, dass der Täter etwa 500 Euro erbeutet hatte. \n"
                    "Ein weiterer Zeuge, Frau Lisa Meier, sah den Täter in einen weißen Toyota Corolla steigen und in Richtung Bahnhof fahren.\n",
                    {
                            {"In welchem Monat fand das Ereignis statt?", {"Juli",      "August",  "September", "Oktober"},   2},
                            {"Um wieviel Uhr fand das Ereignis statt?", {"20:00", "21:00", "22:00", "23:00"}, 1},
                            {"In welchem Kino befand sich die Person?",            {"Kino",           "Filmwelt",        "Lichtspiele",      "Filmtheater"},  1},
                            {"In welcher Straße liegt das Kino?",            {"Hauptstraße",   "Rosenstraße",  "Gartenstraße",   "Bahnhofstraße"}, 1},
                            {"Welche Farbe hatte die Maske des Täters?", {"schwarz", "weiß",   "rot",  "blau"},    1},
                            {"Welche Farbe hatte der Mantel des Täters?",    {"schwarz",         "grau",  "braun",   "grün"},  0},
                            {"Wie groß war der Täter?",                  {"1,60",    "1,70", "1,75", "1,80"}, 2},
                            {"Welches Fahrzeug fuhr der Täter?", {"BMW",  "Mercedes", "Toyota", "Audi"},       2},
                            {"In welche Richtung fuhr der Täter nach dem Überfall?", {"Stadtpark",  "Marktplatz", "Bahnhof",    "Autobahnauffahrt"}, 2},
                            {"Wie viel Geld erbeutete der Täter?",                      {"300 Euro",  "400 Euro",   "500 Euro",   "600 Euro"},         2}
                    }
            },
            {
                    "Am 30. Juli 2024, um circa 10:00 Uhr, war ich im Einkaufszentrum Citti-Park in der Gartenstraße 45. \n"
                    "Plötzlich bemerkte ich, dass ein Mann, etwa 1,75 Meter groß,\n"
                    "mit einem blauen Hemd und einer schwarzen Hose, hektisch durch die Läden ging und mehrere Produkte in seine Tasche steckte. \n"
                    "Als er das Einkaufszentrum verlassen wollte, sprach ihn ein Sicherheitsmitarbeiter an.\n"
                    "Der Mann rannte daraufhin weg und ich sah, wie er in einen silbernen Mercedes\n"
                    "mit dem Kennzeichen KI-KL 5678 stieg und in Richtung Innenstadt fuhr. \n"
                    "Die Polizei kam kurz darauf an und nahm Zeugenaussagen auf. \n"
                    "Die Ladenbesitzerin berichtete, dass der Mann mehrere Elektronikartikel im Wert von 800 Euro gestohlen hatte.\n",
                    {
                            {"In welchem Monat fand das Ereignis statt?", {"Juni",      "Juli",    "August",    "September"}, 1},
                            {"Um wieviel Uhr fand das Ereignis statt?", {"09:00", "10:00", "11:00", "12:00"}, 1},
                            {"In welchem Einkaufszentrum befand sich die Person?", {"Citti-Park",     "Shopping Center", "Einkaufsparadies", "Mall of City"}, 0},
                            {"In welcher Straße liegt das Einkaufszentrum?", {"Hauptstraße",   "Gartenstraße", "Berliner Allee", "Bahnhofstraße"}, 1},
                            {"Welche Farbe hatte das Hemd des Täters?",  {"blau",    "rot",    "grün", "schwarz"}, 0},
                            {"Welche Farbe hatte die Hose des Täters?",      {"schwarz",         "weiß",  "grau",    "braun"}, 0},
                            {"Wie groß war der Täter?",                  {"1,60",    "1,70", "1,75", "1,80"}, 2},
                            {"Welches Auto fuhr der Täter?",     {"BMW",  "Mercedes", "Audi",   "Volkswagen"}, 1},
                            {"Welches Kennzeichen hatte das Auto?",                  {"KI-AB 1234", "KI-CD 5678", "KI-EF 9012", "KI-KL 5678"},       3},
                            {"In welche Richtung fuhr der Täter nach dem Diebstahl?",   {"Stadtpark", "Marktplatz", "Innenstadt", "Autobahn"},         2},
                            {"Wie viel waren die gestohlenen Elektronikartikel wert?",      {"500 Euro", "600 Euro", "700 Euro", "800 Euro"}, 3}
                    }
            },
            {
                    "Am 15. November 2024, gegen 18:30 Uhr, saß ich im Restaurant Gourmet Palace in der Königstraße 17 und genoss mein Abendessen. \n"
                    "Plötzlich sah ich einen Mann durch das Fenster, etwa 1,90 Meter groß, mit einer roten Jacke und\n"
                    "einer schwarzen Mütze, welcher eine Handtasche von einer vorbeigehenden Frau stahl. \n"
                    "Der Mann rannte schnell in Richtung Flughafen. Ich alarmierte sofort die Polizei, die wenige Minuten später eintraf. \n"
                    "Die bestohlene Frau berichtete, dass ihre Handtasche 300 Euro Bargeld sowie wichtige Dokumente enthielt. \n"
                    "Ein weiterer Zeuge, Herr Peter Schmitz, sah den Täter in einen grünen\n"
                    "Opel Corsa mit dem Kennzeichen KI-XY 3456 steigen und wegfahren.\n",
                    {
                            {"In welchem Monat fand das Ereignis statt?", {"September", "Oktober", "November",  "Dezember"},  2},
                            {"Um wieviel Uhr fand das Ereignis statt?", {"17:30", "18:30", "19:30", "20:30"}, 1},
                            {"In welchem Restaurant saß die Person?",              {"Gourmet Palace", "Feinschmecker",   "Delikatessen",     "Essparadies"},  0},
                            {"In welcher Straße liegt das Restaurant?",      {"Hauptstraße",   "Königstraße",  "Marktstraße",    "Gartenstraße"},  1},
                            {"Welche Farbe hatte die Jacke des Täters?", {"blau",    "rot",    "grün", "schwarz"}, 1},
                            {"Welche Art von Kopfbedeckung trug der Täter?", {"Hut",             "Mütze", "Kappe",   "Helm"},  1},
                            {"Wie groß war der Täter?",                  {"1,70",    "1,80", "1,90", "2,00"}, 2},
                            {"Welches Fahrzeug fuhr der Täter?", {"BMW",  "Mercedes", "Opel",   "Volkswagen"}, 2},
                            {"Welches Kennzeichen hatte das Auto?",                  {"KI-AB 1234", "KI-CD 5678", "KI-EF 9012", "KI-XY 3456"},       3},
                            {"In welche Richtung rannte der Täter nach dem Diebstahl?", {"Stadtpark", "Marktplatz", "Flughafen",  "Autobahnauffahrt"}, 2},
                            {"Wie viel Bargeld befand sich in der gestohlenen Handtasche?", {"200 Euro", "250 Euro", "300 Euro", "350 Euro"}, 2}
                    }
            }
    };
}

// get a random question
const QuestionBank::QuestionSet &QuestionBank::getRandomQuestionSet() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _questionSets.size() - 1);
    return _questionSets[dis(gen)];
}
