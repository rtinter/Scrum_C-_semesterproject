#pragma once
#include <map>
#include <memory>
#include <string>
#include "Scene.hpp"

class SceneManager {
    std::map<std::string, std::unique_ptr<Scene>> _scenes;
    std::unique_ptr<Scene> _currentScene;

    SceneManager() : _currentScene(nullptr) {}

public:
    static SceneManager& getInstance();
    void switchTo(std::unique_ptr<Scene> scene);
    void addDefaultScenes();
    void render();
};

