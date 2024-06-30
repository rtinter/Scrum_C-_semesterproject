#include "MemoryGameImageManager.hpp"
#include <iostream>


namespace memory {

    MemoryGameImageManager &MemoryGameImageManager::getInstance() {
        static MemoryGameImageManager instance;
        return instance;
    }

    void MemoryGameImageManager::initialize() {
        loadImages(); // Load the image paths
        for (const auto &path: _imagePaths) {
            sf::Texture texture;
            loadTextureFromFile(path, texture); // Load each texture from file
            _textures.push_back(texture);
        }
    }

    void MemoryGameImageManager::releaseResources() {
        _textures.clear();
    }


    void MemoryGameImageManager::loadImages() {
        for (int i{0}; i < 15; ++i) {
            _imagePaths.push_back("images/image" + std::to_string(i) + ".png");
        }
    }

    void MemoryGameImageManager::loadTextureFromFile(const std::string &path, sf::Texture &texture) {
        if (!texture.loadFromFile(path)) {
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

} // memory