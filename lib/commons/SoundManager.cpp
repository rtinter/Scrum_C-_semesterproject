#pragma once

#include <iostream>
#include "SoundManager.hpp"
#include <SFML/Audio.hpp>
#include <filesystem>

namespace commons {

    std::string const SoundManager::PATH = std::filesystem::current_path().parent_path().parent_path().generic_string() + "/lib/commons/sounds/";

    sf::Sound SoundManager::_activeSound;

    std::unordered_map<commons::Sound, sf::SoundBuffer> SoundManager::_soundBufferMap;

    void SoundManager::loadSounds() {

        // load sound buffers, add new sounds here
        initSoundBuffer(Sound::CLICK, "click.mp3");
        initSoundBuffer(Sound::LASER_GUN, "laser-gun.mp3");

    }

    void SoundManager::initSoundBuffer(commons::Sound sound, std::string const& filename) {

        sf::SoundBuffer soundBuffer;
        if(soundBuffer.loadFromFile(PATH + filename)){
            _soundBufferMap[sound] = soundBuffer;
        } else {
            std::cout << "Error loading sound " << filename << std::endl;
        }

    }

    void SoundManager::playSound(commons::Sound sound) {

        // check if sound manager is initialized
        if(_soundBufferMap.empty()) {
            std::cout << "SoundManager not initialized" << std::endl;
            return;
        }

        // check if sound is in map
        if(!_soundBufferMap.count(sound)) {
            std::cout << "Sound could not be loaded" << std::endl;
            return;
        }

        // play sound
        _activeSound.setBuffer(_soundBufferMap.at(sound));
        _activeSound.play();

    }
}
