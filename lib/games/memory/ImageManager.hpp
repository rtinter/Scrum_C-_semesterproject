#ifndef ATHENA_IMAGEMANAGER_HPP
#define ATHENA_IMAGEMANAGER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <imgui.h>

class ImageManager {
public:
    ImageManager();

    sf::Texture &getTexture(int index);

    int getImageCount() const; // unused
    std::vector<sf::Texture> &getTextures(); // unused

    void setBackgroundColor(ImVec4 color); // unused
    ImVec4 getBackgroundColor() const; // unused
private:
    std::vector<std::string> _imagePaths;
    std::vector<sf::Texture> _textures;
    ImVec4 _backgroundColor;

    void loadImages();

    void loadTextureFromFile(const std::string &path, sf::Texture &texture);
};

#endif //ATHENA_IMAGEMANAGER_HPP