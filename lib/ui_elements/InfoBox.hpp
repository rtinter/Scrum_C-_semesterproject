#pragma once

#include <functional>
#include <Game.hpp>
#include <utility>
#include <optional>
#include "GameSessionManager.hpp"


namespace ui_elements {
    class InfoBox {
        abstract_game::GameID &_gameID;
        bool &_showOverlay;
        std::string _overlayType;
        std::optional<std::string> _gameName;
        std::optional<std::string> _gameDescription;
        std::optional<std::string> _gameRules;
        std::optional<std::string> _gameControls;
        std::optional<std::string> _endGameTitle;
        std::optional<std::string> _endGameText;
        std::function<void()> const &_callback;

    public:
        InfoBox(
                abstract_game::GameID &_gameID,
                bool &_showOverlay,
                std::string _overlayType,
                std::optional<std::string> _gameName,
                std::optional<std::string> _gameDescription,
                std::optional<std::string> _gameRules,
                std::optional<std::string> _gameControls,
                std::function<void()> const &_callback
        );

        InfoBox(
                abstract_game::GameID &_gameID,
                bool &_showOverlay,
                std::string _overlayType,
                std::optional<std::string> _endGameTitle,
                std::optional<std::string> _endGameText,
                std::function<void()> const &_callback
        );

        void render();
    };
}
