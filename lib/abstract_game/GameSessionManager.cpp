#include "GameSessionManager.hpp"

namespace abstract_game {
    void GameSessionManager::startSession(GameID gameID) {
        constexpr int USER_ID{1}; // Default or constant userID
        _currentSession = std::make_shared<GameSession>(gameID, USER_ID);
    }

    void GameSessionManager::endSession() {
        if (_currentSession) {
            _currentSession->end();
            _currentSession.reset();
        }
    }

    std::shared_ptr<GameSession> GameSessionManager::getCurrentSession() {
        return _currentSession;
    }


    std::shared_ptr<GameSession> GameSessionManager::_currentSession;
} // namespace abstract_game
