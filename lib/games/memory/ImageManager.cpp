#include "ImageManager.hpp"
#include <iostream>
#include "Colors.hpp"

ImageManager::ImageManager() : _backgroundColor(commons::Colors::LIGHT_GRAY) {
    loadImages();
    for (const auto& path : _imagePaths) {
        sf::Texture texture;
        loadTextureFromFile(path, texture);
        _textures.push_back(texture);
    }
}

void ImageManager::loadImages() {
    for (int i {0}; i < 15; ++i) {
        _imagePaths.push_back("images/image" + std::to_string(i) + ".png");
    }
}

void ImageManager::loadTextureFromFile(const std::string& path, sf::Texture& texture) {
    if (texture.loadFromFile(path)) {
        std::cout << "Loaded texture from file: " << path << std::endl;
    } else {
        std::cerr << "Failed to load texture from file: " << path << std::endl;
    }
}

sf::Texture& ImageManager::getTexture(int index) {
    if (index < 0 || index >= _textures.size()) {
        static sf::Texture empty;
        return empty;
    }
    return _textures[index];
}

int ImageManager::getImageCount() const { //unused
    return _textures.size();
}

std::vector<sf::Texture>& ImageManager::getTextures() { //unused
    return _textures;
}

void ImageManager::setBackgroundColor(ImVec4 color) { //unused
    _backgroundColor = color;
}

ImVec4 ImageManager::getBackgroundColor() const { //unused
    return _backgroundColor;
}