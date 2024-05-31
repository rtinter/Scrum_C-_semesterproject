#pragma once
#include <map>
#include <memory>
#include <string>
#include "Scene.hpp"

class SceneManager {
    std::map<std::string, std::unique_ptr<Scene>> _scenes;
    Scene* _currentScene {nullptr};


public:
    static SceneManager& getInstance();

    void addScene(const std::string& name, std::unique_ptr<Scene> scene);
    void switchTo(const std::string& name);
    void render();
};
