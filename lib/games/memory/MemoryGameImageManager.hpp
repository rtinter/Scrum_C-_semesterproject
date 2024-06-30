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

        MemoryGameImageManager(const MemoryGameImageManager &) = delete;
        MemoryGameImageManager &operator=(const MemoryGameImageManager &) = delete;
        MemoryGameImageManager(MemoryGameImageManager &&) = delete;
        MemoryGameImageManager &operator=(MemoryGameImageManager &&) = delete;

    private:
        MemoryGameImageManager() = default;
        ~MemoryGameImageManager();

        std::vector<std::string> _imagePaths;
        std::vector<sf::Texture> _textures;

        void loadImages();

        static void loadTextureFromFile(const std::string &path, sf::Texture &texture);

    };

} // namespace memory

#endif //ATHENA_MEMORYGAMEIMAGEMANAGER_HPP