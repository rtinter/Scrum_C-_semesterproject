//
// Created by Admin on 16.06.2024.
//

#include "ImageManager.hpp"
#include <iostream>
#include <SFML/Network.hpp>
#include "Colors.hpp"

ImageManager::ImageManager() : _backgroundColor(commons::Colors::LIGHT_GRAY) {
    loadImages();
    for (const auto& url : _imageUrls) {
        sf::Texture texture;
        loadTextureFromURL(url, texture);
        _textures.push_back(texture);
    }
}

void ImageManager::loadImages() {
    _imageUrls = {
            "https://example.com/image1.png",
            "https://example.com/image2.png",
            "https://example.com/image3.png",
            // Weitere URLs hier hinzufügen
    };
}

void ImageManager::loadTextureFromURL(const std::string& url, sf::Texture& texture) {
    sf::Http http(url);
    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    sf::Http::Response response = http.sendRequest(request);

    if (response.getStatus() == sf::Http::Response::Ok) {
        if (texture.loadFromMemory(response.getBody().c_str(), response.getBody().size())) {
            std::cout << "Loaded texture from URL: " << url << std::endl;
        } else {
            std::cerr << "Failed to load texture from URL: " << url << std::endl;
        }
    } else {
        std::cerr << "Failed to fetch URL: " << url << " - " << response.getStatus() << std::endl;
    }
}

sf::Texture& ImageManager::getTexture(int index) {
    if (index < 0 || index >= _textures.size()) {
        static sf::Texture empty;
        return empty;
    }
    return _textures[index];
}

int ImageManager::getImageCount() const {
    return _textures.size();
}

std::vector<sf::Texture>& ImageManager::getTextures() {
    return _textures;
}

void ImageManager::setBackgroundColor(ImVec4 color) {
    _backgroundColor = color;
}

ImVec4 ImageManager::getBackgroundColor() const {
    return _backgroundColor;
}

