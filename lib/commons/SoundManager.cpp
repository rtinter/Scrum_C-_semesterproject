#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"

#include "SoundManager.hpp"

#include <SFML/Audio.hpp>

#include "Logger.hpp"

namespace commons {
    std::string const SoundManager::PATH{"assets/commons/sounds/"};

    sf::Sound SoundManager::_activeSound;

    std::unordered_map<Sound, sf::SoundBuffer> SoundManager::_soundBufferMap;

    void SoundManager::loadSounds() {
        logger::Logger &logger{logger::Logger::getInstance()};

#if (!defined(_WIN32))
        // only load sounds on windows
        logger << "Sounds currently only supported on Windows, SoundManager not loaded";
        return;
#endif

        // load sound buffers, add new sounds here
        // ReSharper disable once CppDFAUnreachableCode
        initSoundBuffer(Sound::LASER_GUN, "laser-gun.mp3");
        initSoundBuffer(Sound::EXPLOSION, "explosion.mp3");
        initSoundBuffer(Sound::ERROR, "error.mp3");
        initSoundBuffer(Sound::COMPLETE, "complete.mp3");
        initSoundBuffer(Sound::CORRECT, "correct.mp3");
        initSoundBuffer(Sound::BEEP, "beep.mp3");
        initSoundBuffer(Sound::BEEP_FAIL, "beep-fail.mp3");
        initSoundBuffer(Sound::CARD_FLIP, "card-flip.mp3");
        initSoundBuffer(Sound::CLICK, "click.mp3");

        logger << "SoundManager loaded";
    }

    void SoundManager::initSoundBuffer(Sound const sound, std::string const &filename) {
        logger::Logger &logger{logger::Logger::getInstance()};

        if (sf::SoundBuffer soundBuffer; soundBuffer.loadFromFile(PATH + filename)) {
            _soundBufferMap[sound] = soundBuffer;
        } else {
            logger << "Error loading sound: " << filename;
        }
    }

    void SoundManager::playSound(Sound const sound) {
        // ReSharper disable once CppDeprecatedEntity
        playSound(sound, 100.0f);
    }

    void SoundManager::playSound(Sound const sound, int const volumeInPercent) {
        // ReSharper disable once CppDeprecatedEntity
        playSound(sound, volumeInPercent, 1.0f);
    }

    void SoundManager::playSound(Sound sound, int volumeInPercent, float pitch) {
#if (!defined(_WIN32))
        // only play sound on windows
        return;
#endif

        // ReSharper disable once CppDFAUnreachableCode
        logger::Logger &logger{logger::Logger::getInstance()};

        // check if sound manager is initialized
        if (_soundBufferMap.empty()) {
            logger << "SoundManager not initialized";
            return;
        }

        // check if sound is in map
        if (!_soundBufferMap.count(sound)) {
            logger << "Sound could not be loaded";
            return;
        }

        // play sound
        _activeSound.setBuffer(_soundBufferMap.at(sound));
        _activeSound.setVolume(volumeInPercent);
        _activeSound.setPitch(pitch);
        _activeSound.play();

        logger << "Playing Sound";
    }
}

#pragma clang diagnostic pop
