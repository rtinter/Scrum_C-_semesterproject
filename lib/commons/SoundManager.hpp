#pragma once
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // safe wrapped

#include <unordered_map>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>

#include "Sound.hpp"


namespace commons {
    /**
     * @brief The SoundManager class is a singleton class that manages the sound effects.
     *
     * Currently, the SoundManager only supports Windows. There will be no sound on other platforms.
     * To ensure the safe use of sounds, you should use the SoundPolice class instead, which is a wrapper for this class.
     */
    class SoundManager {
        /**
         * The path to the sound files.
         */
        static std::string const PATH;

        /**
         * The active sound.
         */
        static sf::Sound _activeSound;

        /**
         * The sound buffer map.
         */
        static std::unordered_map<Sound, sf::SoundBuffer> _soundBufferMap;

        /**
         * Initializes a sound buffer.
         * @param sound The sound.
         * @param filename The filename.
         */
        static void initSoundBuffer(Sound sound, std::string const &filename);

    public:
        SoundManager() = delete;

        /**
         * Loads all sounds into the sound buffer map.
         */
        static void loadSounds();

        /**
         * Plays a sound.
         * @param sound The sound to play.
         * @deprecated
         */
        [[deprecated("Do not use because this crashes on linux and mac, use commons::SoundPolice::playSound instead")]]
        static void playSound(Sound sound);

        /**
         * Plays a sound with a given volume.
         * @param sound The sound to play.
         * @param volumeInPercent The volume in percent with a default value of 100.
         * @deprecated
         */
        [[deprecated("Do not use because this crashes on linux and mac, use commons::SoundPolice::playSound instead")]]
        static void playSound(Sound sound, int volumeInPercent);

        /**
         * Plays a sound with a given volume and pitch.
         * @param sound The sound to play.
         * @param volumeInPercent The volume in percent with a default value of 100.
         * @param pitch The pitch with a default value of 1.
         * @deprecated
         */
        [[deprecated("Do not use because this crashes on linux and mac, use commons::SoundPolice::playSound instead")]]
        static void playSound(Sound sound, int volumeInPercent, float pitch);
    };
}
