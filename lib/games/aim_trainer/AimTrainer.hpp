#pragma once

#include "Blob.hpp"
#include "Centered.hpp"
#include "Fonts.hpp"
#include "Game.hpp"
#include "InfoBox.hpp"
#include "Overlay.hpp"
#include "SceneManager.hpp"
#include "TextCentered.hpp"
#include <future>
#include <iostream>
#include <thread>

#include "DashboardScene.hpp"
#include "Timer.hpp"
#include "SFML/System/Clock.hpp"

namespace games {

/**
 * @brief The AimTrainer class implements an aim training game.
 *
 * The game spawns blobs (circles) at random positions on the screen, and the player needs to click on them to score points.
 * The game tracks the number of successful hits and missed blobs. The game becomes progressively more challenging as the
 * number of blobs increases and their size decreases over time. A timer limits the game duration.
 */

class AimTrainer : abstract_game::Game {
private:
    std::future<void> _backgroundBlobTask;
    std::future<void> _spawnBlobTask;

    std::vector<aim_trainer::Blob> _currentBlobs;

    int _successCounter {0};
    int _missedCounter {0};

    float _spawnAmount{1};

    sf::Clock _clock;
    sf::Time _elapsedTime;

    std::unique_ptr<ui_elements::Timer> _timer;
    float _missedFactor {1};

    /**
     * @brief Spawns new blobs at random positions within the window.
     */
    void spawnBlobs();

    /**
     * @brief Updates the state of current blobs and handles missed blobs.
     */
    void updateBlobs();
public:
    AimTrainer();

    std::string getName() const override;
    void render() override;
    void renderGame() override;
    void reset() override;
    void start() override;
    void stop() override;
    void updateStatistics() override;
};
}
