//
// Created by zepi on 23.05.24.
//

#ifndef ATHENA_OVERLAY_HPP
#define ATHENA_OVERLAY_HPP

namespace ui_elements {

    class Overlay {
    public:
        explicit Overlay(const char *name, bool &showModal);

        void render();

    private:
        const char *name;
        bool &showModal;
    };

} // ui_elements

#endif //ATHENA_OVERLAY_HPP
