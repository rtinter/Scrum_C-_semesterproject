#pragma once
#include <map>
#include <memory>
#include <string>
#include "Scene.hpp"

class SceneManager {
    std::map<std::string, std::unique_ptr<Scene>> _scenes;
    //Scene* _currentScene {nullptr};
    std::unique_ptr<Scene> _currentScene;

public:
    static SceneManager& getInstance();

    void addScene(const std::string& name, std::unique_ptr<Scene> scene);
    void switchTo(std::unique_ptr<Scene>);

    void render();
};
