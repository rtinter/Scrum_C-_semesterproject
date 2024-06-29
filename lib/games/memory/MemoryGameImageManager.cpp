#include "MemoryGameImageManager.hpp"
#include <iostream>
#include "Colors.hpp"

MemoryGameImageManager& MemoryGameImageManager::getInstance() {
    static MemoryGameImageManager instance;
    return instance;
}

MemoryGameImageManager::MemoryGameImageManager() : _backgroundColor(commons::Colors::LIGHT_GRAY) {
    // Constructor does not load images anymore
}

MemoryGameImageManager::~MemoryGameImageManager() = default;

void MemoryGameImageManager::initialize() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_textures.empty()) {
        loadImages();
        for (const auto& path : _imagePaths) {
            sf::Texture texture;
            loadTextureFromFile(path, texture);
            _textures.push_back(texture);
        }
    }
}

void MemoryGameImageManager::loadImages() {
    for (int i {0}; i < 15; ++i) {
        _imagePaths.push_back("images/image" + std::to_string(i) + ".png");
    }
}

void MemoryGameImageManager::loadTextureFromFile(const std::string& path, sf::Texture& texture) {
    if (texture.loadFromFile(path)) {
        std::cout << "Loaded texture from file: " << path << std::endl;
    } else {
        std::cerr << "Failed to load texture from file: " << path << std::endl;
    }
}

sf::Texture& MemoryGameImageManager::getTexture(int index) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (index < 0 || index >= _textures.size()) {
        static sf::Texture empty;
        return empty;
    }
    return _textures[index];
}

int MemoryGameImageManager::getImageCount() const { //unused
    return _textures.size();
}

std::vector<sf::Texture>& MemoryGameImageManager::getTextures() { //unused
    return _textures;
}

void MemoryGameImageManager::setBackgroundColor(ImVec4 color) { //unused
    _backgroundColor = color;
}

ImVec4 MemoryGameImageManager::getBackgroundColor() const { //unused
    return _backgroundColor;
}




/*
#include "MemoryGameImageManager.hpp"
#include <iostream>
#include "Colors.hpp"

MemoryGameImageManager::MemoryGameImageManager() : _backgroundColor(commons::Colors::LIGHT_GRAY) {
    loadImages();
    for (const auto& path : _imagePaths) {
        sf::Texture texture;
        loadTextureFromFile(path, texture);
        _textures.push_back(texture);
    }
}

void MemoryGameImageManager::loadImages() {
    for (int i {0}; i < 15; ++i) {
        _imagePaths.push_back("images/image" + std::to_string(i) + ".png");
    }
}

void MemoryGameImageManager::loadTextureFromFile(const std::string& path, sf::Texture& texture) {
    if (texture.loadFromFile(path)) {
        std::cout << "Loaded texture from file: " << path << std::endl;
    } else {
        std::cerr << "Failed to load texture from file: " << path << std::endl;
    }
}

sf::Texture& MemoryGameImageManager::getTexture(int index) {
    if (index < 0 || index >= _textures.size()) {
        static sf::Texture empty;
        return empty;
    }
    return _textures[index];
}

int MemoryGameImageManager::getImageCount() const { //unused
    return _textures.size();
}

std::vector<sf::Texture>& MemoryGameImageManager::getTextures() { //unused
    return _textures;
}

void MemoryGameImageManager::setBackgroundColor(ImVec4 color) { //unused
    _backgroundColor = color;
}

ImVec4 MemoryGameImageManager::getBackgroundColor() const { //unused
    return _backgroundColor;
}*/
