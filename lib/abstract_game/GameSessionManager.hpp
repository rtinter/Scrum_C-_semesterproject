#ifndef GAMESESSIONMANAGER_HPP
#define GAMESESSIONMANAGER_HPP

#include "GameSession.hpp"
#include "GameIDs.hpp"
#include <memory>

namespace abstract_game {
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

#endif // GAMESESSIONMANAGER_HPP
