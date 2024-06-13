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

namespace games {
class AimTrainer : abstract_game::Game{
private:
    std::future<void> _backgroundBlobTask;
    std::future<void> _spawnBlobTask;

    std::atomic_bool _cancelBackgroundTask {false};

    std::vector<aim_trainer::Blob> _currentBlobs;

    int _successCounter {0};
    int _missedCounter {0};

    float _spawnAmount{1};

    sf::Clock _clock;
    sf::Time _elapsedTime;

    std::unique_ptr<ui_elements::Timer> _timer;
    float _missedFactor {1};

    void spawnBlobs();
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