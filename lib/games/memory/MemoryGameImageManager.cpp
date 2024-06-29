#include "MemoryGameImageManager.hpp"
#include <iostream>
#include "Colors.hpp"

namespace memory {

    MemoryGameImageManager &MemoryGameImageManager::getInstance() {
        static MemoryGameImageManager instance;
        return instance;
    }

    MemoryGameImageManager::MemoryGameImageManager() : _backgroundColor(commons::Colors::LIGHT_GRAY) {
        // Constructor does not load images anymore
    }

    MemoryGameImageManager::~MemoryGameImageManager() {
        releaseResources(); // Ensure resources are released
    };

    void MemoryGameImageManager::initialize() {
        loadImages();
        for (const auto &path: _imagePaths) {
            sf::Texture texture;
            loadTextureFromFile(path, texture);
            _textures.push_back(texture);
        }
    }

    void MemoryGameImageManager::releaseResources() {
        _textures.clear(); // Clear textures to release OpenGL resources
    }


    void MemoryGameImageManager::loadImages() {
        for (int i{0}; i < 15; ++i) {
            _imagePaths.push_back("images/image" + std::to_string(i) + ".png");
        }
    }

    void MemoryGameImageManager::loadTextureFromFile(const std::string &path, sf::Texture &texture) {
        if (texture.loadFromFile(path)) {
            std::cout << "Loaded texture from file: " << path << std::endl;
        } else {
            std::cerr << "Failed to load texture from file: " << path << std::endl;
        }
    }

    sf::Texture &MemoryGameImageManager::getTexture(int index) {
        if (index < 0 || index >= _textures.size()) {
            static sf::Texture empty;
            return empty;
        }
        return _textures[index];
    }

    int MemoryGameImageManager::getImageCount() const { //unused
        return _textures.size();
    }

    std::vector<sf::Texture> &MemoryGameImageManager::getTextures() { //unused
        return _textures;
    }

    void MemoryGameImageManager::setBackgroundColor(ImVec4 color) { //unused
        _backgroundColor = color;
    }

    ImVec4 MemoryGameImageManager::getBackgroundColor() const { //unused
        return _backgroundColor;
    }

} // memory