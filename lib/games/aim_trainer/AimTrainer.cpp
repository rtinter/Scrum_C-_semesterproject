#include "AimTrainer.hpp"
#include "Window.hpp"

int randomPos(int n){
    return rand() % n + 1;
}

std::mutex _mutex;

void games::AimTrainer::spawnBlobBackgroundTask(){
    while(!_cancelBackgroundTask){
        updateBlobs();
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
    std::cout << "Canceled Background Task" << std::endl;
}

void games::AimTrainer::spawnBlobs(){
    const auto size = ImGui::GetWindowContentRegionMax();
    int windowWidth {static_cast<int>(size.x)};
    int windowHeight {static_cast<int>(size.y)};

    while(!_cancelBackgroundTask){
        std::lock_guard<std::mutex> guard(_mutex);
        for(int i {0}; i < _spawnAmount; ++i){
            _currentBlobs.emplace_back(
                    randomPos(windowWidth),
                    randomPos(windowHeight),
                    _currentBlobs.size() + 1
            );
            std::this_thread::sleep_for(std::chrono::milliseconds (rand()/100));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (2500));
    }
    std::cout << "Canceled Background Task" << std::endl;
}

void games::AimTrainer::updateBlobs(){
    std::lock_guard<std::mutex> guard(_mutex);
    // remove blobs that are to be disposed
    _currentBlobs.erase(
            std::remove_if(
            _currentBlobs.begin(),
            _currentBlobs.end(),
            [this](aim_trainer::Blob &b){
        bool dispose = b.canBeDisposed();
        if(b.canBeDisposed())
            _missedCounter++;
        return dispose;
    }), _currentBlobs.end());


    // decrease blob size
    for(auto &blob : _currentBlobs){
        blob.decrease((1.0/blob.getRadius()));
    }
}

void games::AimTrainer::render() {
    ui_elements::InfoBox(_showInfobox, _gameName, _gameDescription, _gameRules, _gameControls, [this] {
        start();
    }).render();

    if(ImGui::IsMouseDown(0)){
        auto const mousePos = ImGui::GetMousePos();

        std::vector<aim_trainer::Blob> blobsToDelete;
        _currentBlobs.erase(
                std::remove_if(
                _currentBlobs.begin(),
                _currentBlobs.end(),
                [this, mousePos](aim_trainer::Blob &b){
            const auto coords = b.getCoords();

            const float dx = coords.x - mousePos.x;
            const float dy = coords.y - mousePos.y;
            const float dist =  dx * dx + dy * dy;

            // increment successful clicks of blobs
            bool inCircle = dist <= b.getRadius() * b.getRadius();
            if(inCircle)
                _successCounter++;
                    return inCircle;
        }), _currentBlobs.end());
    }


    ui_elements::Overlay("Endbox", _showEndbox).render([this]() {
        ImGui::PushFont(commons::Fonts::_header2);
        ui_elements::TextCentered(std::move(_endboxTitle));
        ImGui::PopFont();
        ui_elements::TextCentered(std::move(_endboxText));

        ui_elements::Centered([this]() {
            if (ImGui::Button("Versuch es nochmal")) {
                start();
            }

            if (ImGui::Button("Zurück zur Startseite")) {
                scene::SceneManager::getInstance().switchTo(std::make_unique<scene::DashboardScene>());
            }
        });
    });

    if (_isGameRunning) {
        renderGame();
    }
}

void games::AimTrainer::renderGame() {
    ui_elements::Window("Aim Trainer Game").render([this] {
        for(const auto &blob : _currentBlobs){
            blob.render();
        }
    });
}

void games::AimTrainer::reset() {
}

void games::AimTrainer::start() {
    // draw initial blob

    _isGameRunning = true;
    _showEndbox = false;

    _spawnBlobTask = std::async(std::launch::async, [this](){
        spawnBlobs();
    });
    _backgroundBlobTask = std::async(std::launch::async, [this](){
        spawnBlobBackgroundTask();
    });
}

void games::AimTrainer::stop() {
}

void games::AimTrainer::updateStatistics() {
}

std::string games::AimTrainer::getName() const {
    return "AimTrainer";
}

games::AimTrainer::~AimTrainer() {
    _cancelBackgroundTask.store(true);
}

games::AimTrainer::AimTrainer() {
    _gameName = "Aim Trainer";
    _gameDescription = "Ziel treffen";
    _gameRules = "Das ist nicht so kompliziert";
    _gameControls = "";
}
