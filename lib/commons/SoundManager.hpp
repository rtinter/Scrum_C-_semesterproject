#pragma once

#include "Sound.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "unordered_map"

namespace commons {
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
        static std::unordered_map<commons::Sound, sf::SoundBuffer> _soundBufferMap;

        /**
         * Initializes a sound buffer.
         * @param sound The sound.
         * @param filename The filename.
         */
        static void initSoundBuffer(commons::Sound sound, std::string const& filename);

    public:
        SoundManager() = delete;

        /**
         * Loads all sounds into the sound buffer map.
         */
        static void loadSounds();

        /**
         * Plays a sound.
         * @param sound The sound to play.
         */
        static void playSound(commons::Sound sound);

        /**
         * Plays a sound with a given volume.
         * @param sound The sound to play.
         * @param volumeInPercent The volume in percent with a default value of 100.
         */
        static void playSound(commons::Sound sound, int volumeInPercent);

        /**
         * Plays a sound with a given volume and pitch.
         * @param sound The sound to play.
         * @param volumeInPercent The volume in percent with a default value of 100.
         * @param pitch The pitch with a default value of 1.
         */
        static void playSound(commons::Sound sound, int volumeInPercent, float pitch);
    };
}