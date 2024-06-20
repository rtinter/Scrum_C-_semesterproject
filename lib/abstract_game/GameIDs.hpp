#ifndef GAMEIDS_HPP
#define GAMEIDS_HPP
#include <string>

namespace abstract_game {
    enum class GameID {
        REACTION = 1001,
        COLOR_MATCH = 1002,
        AIM_TRAINER = 1003,
        LETTER_SALAD = 1004,
        TYPERACER = 1005,
        REMEMBERING = 1006,
        CALC = 1006,
        MATRIX = 1007,
        ROWS_OF_NUMBERS = 1008,
        MEMORY = 1009,
        SEQUENCE = 1011
    };

    static std::string getGameName(GameID gameID) {
        switch (gameID) {
            case GameID::REACTION:
                return "Reaktion";
            case GameID::COLOR_MATCH:
                return "Farbe & Text";
            case GameID::AIM_TRAINER:
                return "Aim Trainer";
            case GameID::LETTER_SALAD:
                return "Buchstabensalat";
            case GameID::TYPERACER:
                return "TypeRacer";
            case GameID::REMEMBERING:
                return "Fakten merken";
            case GameID::MATRIX:
                return "Matrix";
            case GameID::SEQUENCE:
                return "Sequence";
            default:
                return "Unknown";
        }
    }
} // namespace abstract_game

#endif // GAMEIDS_HPP

