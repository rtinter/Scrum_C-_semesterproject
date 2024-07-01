#ifndef ATHENA_MEMORYGAMEIMAGEMANAGER_HPP
#define ATHENA_MEMORYGAMEIMAGEMANAGER_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <imgui.h>

namespace memory {
    /**
     * @brief MemoryGameImageManager class. Manages the images for the Memory game.
     */
    class MemoryGameImageManager {
    public:
        /**
         * @brief Accessor for the singleton instance of the MemoryGameImageManager.
         * @return Reference to the singleton instance.
         */
        static MemoryGameImageManager &getInstance();

        /**
         * @brief Initializes the image manager by loading textures.
         */
        void initialize();

        /**
         * @brief Releases the loaded textures to free resources.
         */
        void releaseResources();

        /**
         * @brief Gets the texture at the specified index.
         * @param index The index of the texture.
         * @return Reference to the texture at the given index.
         */
        sf::Texture &getTexture(int index);

        // Deleted these to strictly enforce Singleton behavior
        MemoryGameImageManager(const MemoryGameImageManager &) = delete;
        MemoryGameImageManager &operator=(const MemoryGameImageManager &) = delete;
        MemoryGameImageManager(MemoryGameImageManager &&) = delete;
        MemoryGameImageManager &operator=(MemoryGameImageManager &&) = delete;

    private:
        /**
         * @brief Private constructor to enforce singleton pattern.
         */
        MemoryGameImageManager() = default;

        /**
         * @brief Destructor that ensures resources are released.
         */
        ~MemoryGameImageManager() = default;

        /**
         * @brief Loads the image paths into the _imagePaths vector.
         */
        void loadImages();

        /**
         * @brief Loads a texture from a file.
         * @param path The file path of the texture.
         * @param texture The texture object to load the image into.
         */
        static void loadTextureFromFile(const std::string &path, sf::Texture &texture);

        std::vector<std::string> _imagePaths;
        std::vector<sf::Texture> _textures;
    };

} // namespace memory

#endif //ATHENA_MEMORYGAMEIMAGEMANAGER_HPP