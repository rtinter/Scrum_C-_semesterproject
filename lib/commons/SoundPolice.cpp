//
// Created by Benjamin Puhani (941077) on 14.06.2024.
//

#include "SoundPolice.hpp"
#include "SoundManager.hpp"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // safe wrapped

namespace commons {

    void SoundPolice::safePlaySound(Sound sound) {
        safePlaySound(sound, 100);
    }
    void SoundPolice::safePlaySound(Sound sound, int volumeInPercent) {
        safePlaySound(sound, volumeInPercent, 1.0f);
    }

    void SoundPolice::safePlaySound(Sound sound, int volumeInPercent, float pitch) {
#if (defined(_WIN32))
        // load the sounds
        commons::SoundManager::playSound(sound, volumeInPercent, pitch);
#endif
    }
}
