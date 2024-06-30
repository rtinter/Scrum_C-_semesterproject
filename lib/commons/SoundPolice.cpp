#include "SoundPolice.hpp"

#if (defined(_WIN32))

#include "SoundManager.hpp"

#endif


#pragma GCC diagnostic ignored "-Wdeprecated-declarations" // safe wrapped

namespace commons {
    // the sounds are only supported on windows, so we use maybe_unused for other systems to ensure that the compiler does not throw a warning
    void SoundPolice::safePlaySound([[maybe_unused]] Sound sound) {
#if (defined(_WIN32))
        // the sounds are only supported on windows
        commons::SoundManager::playSound(sound);
#endif
    }

    void SoundPolice::safePlaySound([[maybe_unused]] Sound sound, [[maybe_unused]] int volumeInPercent) {
#if (defined(_WIN32))
        // the sounds are only supported on windows
        commons::SoundManager::playSound(sound, volumeInPercent);
#endif
    }

    void SoundPolice::safePlaySound([[maybe_unused]] Sound sound,
                                    [[maybe_unused]] int volumeInPercent,
                                    [[maybe_unused]] float pitch) {
#if (defined(_WIN32))
        // the sounds are only supported on windows
        commons::SoundManager::playSound(sound, volumeInPercent, pitch);
#endif
    }
}
