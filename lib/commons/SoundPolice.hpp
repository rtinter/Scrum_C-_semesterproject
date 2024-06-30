//
// Created by Benjamin Puhani (941077) on 14.06.2024.
//

#ifndef ATHENA_LIB_COMMONS_SOUNDPOLICE_HPP_
#define ATHENA_LIB_COMMONS_SOUNDPOLICE_HPP_

#include "Sound.hpp"

using Sound = commons::Sound;

namespace commons {

    /**
     * Because, Sounds currently only work on Windows,
     * and the class SoundManager has dependencies, that crash the game
     * on mac and linux we wrap this function with this class.
     */
    class SoundPolice {
    public:
        static void safePlaySound([[maybe_unused]] Sound sound);
        static void safePlaySound(Sound sound, int volumeInPercent);
        static void safePlaySound(Sound sound, int volumeInPercent, float pitch);
    };
}

#endif //ATHENA_LIB_COMMONS_SOUNDPOLICE_HPP_
