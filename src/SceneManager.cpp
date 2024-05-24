//
// Created by jo on 5/24/24.
//

#include "SceneManager.hpp"
#include "TestGame.hpp"

manager::SceneManager manager::SceneManager::_instance;
manager::SceneManager::SceneManager() {
}


manager::SceneManager manager::SceneManager::getInstance() {
    return _instance;
}

void manager::SceneManager::handleEvents(sf::RenderWindow &window) {
    sf::Event evt;
    while(window.pollEvent(evt)){
        if(_currentScene){
            _currentScene->handleEvents(evt);
        }
    }
}

void manager::SceneManager::switchScene(std::unique_ptr<scene::SceneContainer> scene) {
    _currentScene = std::move(scene);
}

void manager::SceneManager::render(sf::RenderWindow &window) {}

void manager::SceneManager::update() {
    if(_currentScene){
        _currentScene->update();
    }
}