#include "GameSessionManager.hpp"

namespace abstract_game {

    void GameSessionManager::startSession(GameID gameID) {
        int const userID{1}; // Default or constant userID
        _currentSession = std::make_shared<GameSession>(gameID, userID);
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