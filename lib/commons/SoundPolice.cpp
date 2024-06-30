#include "SoundPolice.hpp"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // safe wrapped

namespace commons {

    void SoundPolice::safePlaySound(Sound sound) {
#if (defined(_WIN32))
        // the sounds are only supported on windows
        commons::SoundManager::playSound(sound);
#endif
    }

    void SoundPolice::safePlaySound(Sound sound, int volumeInPercent) {
#if (defined(_WIN32))
        // the sounds are only supported on windows
        commons::SoundManager::playSound(sound, volumeInPercent);
#endif
    }

    void SoundPolice::safePlaySound(Sound sound, int volumeInPercent, float pitch) {
#if (defined(_WIN32))
        // the sounds are only supported on windows
        commons::SoundManager::playSound(sound, volumeInPercent, pitch);
#endif
    }
}
