#ifndef ATHENA_IMAGEMANAGER_HPP
#define ATHENA_IMAGEMANAGER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <imgui.h>

class ImageManager {
public:
    static ImageManager& getInstance(); // Singleton instance accessor

    sf::Texture &getTexture(int index);

    int getImageCount() const; // unused
    std::vector<sf::Texture> &getTextures(); // unused

    void setBackgroundColor(ImVec4 color); // unused
    ImVec4 getBackgroundColor() const; // unused

    ImageManager(const ImageManager&) = delete; // Delete copy constructor
    ImageManager& operator=(const ImageManager&) = delete; // Delete copy assignment
    ImageManager(ImageManager&&) = delete; // Delete move constructor
    ImageManager& operator=(ImageManager&&) = delete; // Delete move assignment

private:
    ImageManager(); // Private constructor
    ~ImageManager(); // Private destructor

    std::vector<std::string> _imagePaths;
    std::vector<sf::Texture> _textures;
    ImVec4 _backgroundColor;

    void loadImages();
    static void loadTextureFromFile(const std::string &path, sf::Texture &texture);
};

#endif //ATHENA_IMAGEMANAGER_HPP




/*
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

#endif //ATHENA_IMAGEMANAGER_HPP*/
