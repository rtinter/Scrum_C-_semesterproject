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
class AimTrainer : Game{
private:
    std::future<void> _backgroundBlobTask;
    std::future<void> _spawnBlobTask;

    std::atomic_bool _cancelBackgroundTask {false};

    std::vector<aim_trainer::Blob> _currentBlobs;

    std::atomic_int _successCounter {0};
    std::atomic_int _missedCounter {0};

    std::atomic_int _spawnAmount{3};

    void spawnBlobBackgroundTask();
    void spawnBlobs();
    void updateBlobs();
public:
    AimTrainer();
    ~AimTrainer() override;

    std::string getName() const override;
    void render() override;
    void renderGame() override;
    void reset() override;
    void start() override;
    void stop() override;
    void updateStatistics() override;
};
}