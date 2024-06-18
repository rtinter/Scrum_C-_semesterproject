//
// Created by Admin on 16.06.2024.
//

#ifndef ATHENA_IMAGEMANAGER_HPP
#define ATHENA_IMAGEMANAGER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <imgui.h>

class ImageManager {
public:
    ImageManager();

    sf::Texture& getTexture(int index);
    int getImageCount() const;
    std::vector<sf::Texture>& getTextures();

    void setBackgroundColor(ImVec4 color);
    ImVec4 getBackgroundColor() const;

private:
    std::vector<std::string> _imageUrls;
    std::vector<sf::Texture> _textures;
    ImVec4 _backgroundColor;

    void loadImages();
    void loadTextureFromURL(const std::string& url, sf::Texture& texture);
};

#endif //ATHENA_IMAGEMANAGER_HPP


