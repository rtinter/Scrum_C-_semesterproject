#ifndef ATHENA_MEMORYGAMEIMAGEMANAGER_HPP
#define ATHENA_MEMORYGAMEIMAGEMANAGER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <imgui.h>

namespace memory {

    class MemoryGameImageManager {
    public:
        static MemoryGameImageManager &getInstance(); // Singleton instance accessor

        void initialize(); // Initialization method to load textures
        void releaseResources(); // Method to release textures
        sf::Texture &getTexture(int index);

        int getImageCount() const; // unused
        std::vector<sf::Texture> &getTextures(); // unused

        void setBackgroundColor(ImVec4 color); // unused
        ImVec4 getBackgroundColor() const; // unused

        MemoryGameImageManager(const MemoryGameImageManager &) = delete; // Delete copy constructor
        MemoryGameImageManager &operator=(const MemoryGameImageManager &) = delete; // Delete copy assignment
        MemoryGameImageManager(MemoryGameImageManager &&) = delete; // Delete move constructor
        MemoryGameImageManager &operator=(MemoryGameImageManager &&) = delete; // Delete move assignment


    private:
        MemoryGameImageManager(); // Private constructor
        ~MemoryGameImageManager(); // Private destructor

        std::vector<std::string> _imagePaths;
        std::vector<sf::Texture> _textures;
        ImVec4 _backgroundColor;

        void loadImages();

        static void loadTextureFromFile(const std::string &path, sf::Texture &texture);

    };

} // namespace memory

#endif //ATHENA_MEMORYGAMEIMAGEMANAGER_HPP