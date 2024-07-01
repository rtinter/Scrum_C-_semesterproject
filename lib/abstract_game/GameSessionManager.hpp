#ifndef GAMESESSIONMANAGER_HPP
#define GAMESESSIONMANAGER_HPP

#include "GameSession.hpp"
#include "GameIDs.hpp"
#include <memory>

namespace abstract_game {
    /**
     * @brief Manages the game sessions.
     *
     * This class is responsible for starting, ending, and managing the current game session.
     */
    class GameSessionManager {
    public:
        GameSessionManager() = delete;

        /**
         * @brief Starts a new game session.
         *
         * This method initializes a new game session with the specified game ID.
         *
         * @param gameID The ID of the game to start a session for.
         */
        static void startSession(GameID gameID);

        /**
         * @brief Ends the current game session.
         *
         * This method ends the current game session and saves the session data.
         */
        static void endSession();

        /**
         * @brief Gets the current game session.
         *
         * This method returns a shared pointer to the current game session.
         *
         * @return A shared pointer to the current game session.
         */
        static std::shared_ptr<GameSession> getCurrentSession();


    private:

        static std::shared_ptr<GameSession> _currentSession; ///< The current game session.
    };
} // namespace abstract_game

#endif // GAMESESSIONMANAGER_HPP
