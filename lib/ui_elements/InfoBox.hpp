#pragma once
#include <functional>


namespace ui_elements {
    class InfoBox {
        bool &_showOverlay;
        const char *_gameName;
        const char *_gameDescription;
        const char *_gameRules;
        const char *_gameControls;
        const std::function<void()> &_startCallback;

    public:
        InfoBox(
            bool &showOverlay,
            const char *gameName,
            const char *gameDescription,
            const char *gameRules,
            const char *gameControls,
            const std::function<void()> &startCallback
        );

        void render();
    };
}
