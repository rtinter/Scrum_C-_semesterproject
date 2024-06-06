#pragma once
#include <map>
#include <memory>
#include <string>
#include "Scene.hpp"

class SceneManager {
    std::map<std::string, std::unique_ptr<Scene>> scenes;
    std::unique_ptr<Scene> currentScene;

    SceneManager() : currentScene(nullptr) {}

public:
    static SceneManager& getInstance();

    // void addScene(std::unique_ptr<Scene> scene);
    void switchTo(std::unique_ptr<Scene> scene);
    void addDefaultScenes();
    void render();
};
