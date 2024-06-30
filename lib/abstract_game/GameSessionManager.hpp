#pragma once

#include <memory>

#include "GameIDs.hpp"
#include "GameSession.hpp"

namespace abstract_game {
    /**
     * @brief The GameSessionManager class is responsible for managing game sessions.
     *
     * This class provides methods to start, end, and retrieve the current game session.
     */
    class GameSessionManager {
    public:
        GameSessionManager() = delete;

        static void startSession(GameID gameID);

        static void endSession();

        static std::shared_ptr<GameSession> getCurrentSession();

    private:
        static std::shared_ptr<GameSession> _currentSession;
    };
} // namespace abstract_game
