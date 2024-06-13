//
// Created by Admin on 07.06.2024.
//

#ifndef GAMESESSIONMANAGER_HPP
#define GAMESESSIONMANAGER_HPP

#include "GameSession.hpp"
#include "GameIDs.hpp"
#include <memory>

namespace abstract_game {
    class GameSessionManager {
    public:
        static GameSessionManager &getInstance() {
            static GameSessionManager instance;
            return instance;
        }

        void startSession(GameID gameID) {
            int const userID{1}; // Default or constant userID
            _currentSession = std::make_unique<GameSession>(gameID, userID);
        }

        void endSession() {
            if (_currentSession) {
                _currentSession->end();
                _currentSession.reset();
            }
        }

        GameSession *getCurrentSession() const {
            return _currentSession.get();
        }

    private:
        GameSessionManager() = default;

        std::unique_ptr<GameSession> _currentSession;
    };
} // namespace abstract_game

#endif // GAMESESSIONMANAGER_HPP
