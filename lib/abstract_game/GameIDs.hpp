#pragma once

#include <string>

namespace abstract_game {
    /*********************************
    * Enumeration for different Game IDs.
    * Each game is assigned a unique integer identifier.
    ***********************************/
    enum class GameID {
        REACTION = 1001,
        COLOR_MATCH = 1002,
        AIM_TRAINER = 1003,
        LETTER_SALAD = 1004,
        TYPERACER = 1005,
        CALC = 1006,
        MATRIX = 1007,
        ROWS_OF_NUMBERS = 1008,
        REMEMBERING = 1009,
        ANALOGY = 1010,
        SEQUENCE = 1011,
        ROWS_OF_SYMBOLS = 1012,
        ABSURD_QUESTIONS = 1013,
        DIAGRAM = 1014,
        MEMORY = 1015
    };

    /*********************************
    * Retrieves the name of the game corresponding to the given GameID.
    * @param gameID The unique identifier of the game.
    * @return The name of the game as a string. Returns "Unknown" if the GameID is not recognized.
    ***********************************/
    static std::string getGameName(GameID const gameID) {
        switch (gameID) {
            case GameID::REACTION:
                return "Reaktion";
            case GameID::COLOR_MATCH:
                return "Farbe & Wort";
            case GameID::AIM_TRAINER:
                return "Aim Trainer";
            case GameID::LETTER_SALAD:
                return "Buchstabensalat";
            case GameID::TYPERACER:
                return "TypeRacer";
            case GameID::CALC:
                return "Schnelles Rechnen";
            case GameID::MATRIX:
                return "Matrix";
            case GameID::ROWS_OF_NUMBERS:
                return "Zahlenreihen";
            case GameID::REMEMBERING:
                return "Fakten merken";
            case GameID::ANALOGY:
                return "Analogie";
            case GameID::SEQUENCE:
                return "Sequence";
            case GameID::ROWS_OF_SYMBOLS:
                return "Symbolreihen";
            case GameID::ABSURD_QUESTIONS:
                return "Schlussfolgerungen";
            case GameID::MEMORY:
                return "Memory";
            case GameID::DIAGRAM:
                return "Diagramm analysieren";
            default:
                return "Unknown";
        }
    }
} // namespace abstract_game
