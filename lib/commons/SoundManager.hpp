#pragma once

#include "Sound.hpp"
#include "SFML/Audio/Music.hpp"
#include "SFML/Audio/Sound.hpp"
#include "unordered_map"

namespace commons {
    class SoundManager {

        static std::string const PATH;

        static sf::Sound _activeSound;

        static std::unordered_map<commons::Sound, sf::SoundBuffer> _soundBufferMap;

        static void initSoundBuffer(commons::Sound sound, std::string const& filename);

    public:
        SoundManager() = delete;

        static void loadSounds();
        static void playSound(commons::Sound sound);
        static void playSound(commons::Sound sound, int volumeInPercent);
        static void playSound(commons::Sound sound, int volumeInPercent, float pitch);
    };
}