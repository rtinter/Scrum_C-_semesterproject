//
// Created by jo on 5/23/24.
//

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include "StyleManager.hpp"
#include "Fonts.hpp"
#include "Colors.hpp"
#include "ColorTheme.hpp"

#ifndef ATHENA_TESTGAME_HPP
#define ATHENA_TESTGAME_HPP

#include "../../abstract_game/Game.hpp"
#include "../../scene/SceneContainer.hpp"

class TestGame : Game, scene::SceneContainer {
    void start() override;
    void stop() override;

    void render() override;
    void update() override;

    void handleEvents(sf::Event evt) override;

    std::string getGameInfo() override;

    void updateStatistics() override;

    void reset() override;
};


#endif //ATHENA_TESTGAME_HPP