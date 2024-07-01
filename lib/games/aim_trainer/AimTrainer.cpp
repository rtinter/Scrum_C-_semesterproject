#include "AimTrainer.hpp"

#include <algorithm>
#include "Window.hpp"
#include "SoundPolice.hpp"
#include "WindowConfig.hpp"

int randomPos(int n) {
    return rand() % n + 1;
}

void games::AimTrainer::spawnBlobs() {
    int const windowWidth{WindowConfig::WINDOW_WIDTH};
    int const windowHeight{WindowConfig::WINDOW_HEIGHT};

    if(_spawnAmount >= 1){
        commons::SoundPolice::safePlaySound(commons::Sound::CLICK, 30, 3.f);
    }

    for (int i{0}; i < _spawnAmount; ++i) {
        int x{randomPos(windowWidth)};
        x = std::max(x, 240);
        if (x > windowWidth)
            x = windowWidth - 240;
        int y{randomPos(windowHeight)};

        y = std::max(y, 240);
        if (y > windowHeight)
            y = windowHeight - 240;

        _currentBlobs.emplace_back(
                x,
                y,
                _currentBlobs.size() + 1
        );
    }
}

void games::AimTrainer::updateBlobs() {
    // remove blobs that are to be disposed
    int missed{0};
    _currentBlobs.erase(
            std::remove_if(
                    _currentBlobs.begin(),
                    _currentBlobs.end(),
                    [&missed](aim_trainer::Blob &b) {

                        bool dispose{b.canBeDisposed()};
                        if (dispose)
                            missed++;
                        return dispose;
                    }), _currentBlobs.end());

    _missedCounter += missed;

    // decrease blob size
    for (auto &blob: _currentBlobs) {
        blob.decrease((1.0 / (200)));
    }
}

void games::AimTrainer::render() {
    ui_elements::InfoBox(_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                         [this] {
                             start();
                         }).render();

    if (ImGui::IsMouseClicked(0)) {
        auto const mousePos{ImGui::GetMousePos()};

        std::vector<aim_trainer::Blob> blobsToDelete;
        bool hit{false};
        _currentBlobs.erase(
                std::remove_if(
                        _currentBlobs.begin(),
                        _currentBlobs.end(),
                        [this, &hit, mousePos](aim_trainer::Blob &b) {

                            auto const coordsx{b.getCoords().x};
                            auto const coordsy{b.getCoords().y};

                            float const dx{coordsx - mousePos.x};
                            float const dy{coordsy - mousePos.y};
                            float const dist{dx * dx + dy * dy};

                            // increment successful clicks of blobs
                            bool const inCircle{dist <= b.getRadius() * b.getRadius()};
                            if (inCircle) {
                                _successCounter++;
                                hit = true;
                            }
                            return inCircle;
                        }), _currentBlobs.end());

        if (!hit && _timer) {
            _timer->reduceTime(hit ? 2 : 2 * (_missedFactor));
            _missedFactor += 0.25;
            _missedCounter++;
        }
    }

    ui_elements::InfoBox(_gameID, _showEndBox, "Endbox", _endBoxTitle, _endBoxText, [this] {
        reset();
        start();
    }).render();

    if (_isGameRunning) {
        renderGame();
    }
}

void games::AimTrainer::renderGame() {
    ImGui::PushStyleColor(ImGuiCol_WindowBg, commons::Colors::LIGHT_GRAY);
    ui_elements::Window("Aim Trainer").render([this] {
        _timer->render();
        if (_timer->isExpiredNow()) {
            stop();
        }
        _elapsedTime = _clock.getElapsedTime();
        if (_elapsedTime.asSeconds() >= 2) {
            // Restart the clock to measure the next interval
            spawnBlobs();
            _clock.restart();
            _spawnAmount += 0.15;
        }

        ImGui::PushFont(commons::Fonts::_header2);
        ui_elements::TextCentered(std::move(("Hit: " + std::to_string(_successCounter)).c_str()));
        ImGui::PopFont();
        ui_elements::TextCentered(std::move(("Missed: " + std::to_string(_missedCounter)).c_str()));
        updateBlobs();
        for (const auto &blob: _currentBlobs) {
            blob.render();
        }
    });
    ImGui::PopStyleColor();
}

void games::AimTrainer::reset() {
    _successCounter = 0;
    _missedCounter = 0;
    _missedFactor = 1;
    _spawnAmount = 1;
    _currentBlobs.clear();
}

void games::AimTrainer::start() {
    _isGameRunning = true;
    _showEndBox = false;

    _timer = std::make_unique<ui_elements::Timer>("Aim Trainer", 60);
    _timer->start();

    spawnBlobs();
}

void games::AimTrainer::stop() {
    _endBoxText = "Hit: " + std::to_string(_successCounter) + "\nMissed: " + std::to_string(_missedCounter);
    updateStatistics();
    _isGameRunning = false;
    _showEndBox = true;
}

void games::AimTrainer::updateStatistics() {
    abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("Treffer",
                                                                                 _successCounter);
}

std::string games::AimTrainer::getName() const {
    return "AimTrainer";
}

games::AimTrainer::AimTrainer() : Game(abstract_game::GameID::AIM_TRAINER) {
    _gameName = "Aim Trainer";
    _gameDescription = R"(
Willkommen in der Welt von "Circle Strike", dem fesselnden Aim Trainer,
der deine Zielpräzision auf die Probe stellt und auf die nächste Stufe hebt.
Perfekt für Gamer, die ihre Fähigkeiten schärfen wollen, oder für jeden,
der seine Mausgenauigkeit und Reaktionszeit verbessern möchte.
"Circle Strike" bietet eine einfache, doch herausfordernde Spielmechanik,
die dich nicht mehr loslassen wird.
    )";
    _gameRules = "Klicke nur auf die Kreise, nirgendswo anders hin!";
    _gameControls = "";
}
