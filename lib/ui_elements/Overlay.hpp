#pragma once
#include <functional>


namespace ui_elements {

    class Overlay {
    public:
        explicit Overlay(const char *name, bool &showModal);

        void render(std::function<void()> const &callback) const;

    private:
        const char *_name;
        bool &_showModal;
    };

} // ui_elements
