#ifndef ATHENA_GAMESESSION_HPP
#define ATHENA_GAMESESSION_HPP

#include <string>
#include <chrono>
#include <utility>

/**
 * @brief Struct for holding game session information.
 *
 * This struct holds information about a game session.
 */
struct GameSession {

    GameSession(int gameID, int userID);

    // General information
    int gameID;
    int userID;

    // Session information
    size_t gameSessionUID;
    std::chrono::steady_clock::time_point startPoint;
    std::chrono::steady_clock::time_point endPoint;
    bool ended;

    /**
     * @brief Calculates the game session UID.
     *
     * This method calculates a unique identifier for the game session.
     *
     * @return The game session UID.
     */
    static size_t calcGameSessionUID();

    /**
     * @brief Save the current time as the end time of the game session.
     *
     * This method saves the current time as the end time of the game session.
     */
    void end();
};

#endif //ATHENA_GAMESESSION_HPP
