//
// Created by zepi on 23.05.24.
//

#ifndef ATHENA_OVERLAY_HPP
#define ATHENA_OVERLAY_HPP

namespace ui_elements {

    class Overlay {
    public:
        explicit Overlay(const char *name, bool &showModal);

        Overlay();

        //template zur übergabe einer LambdaFunktion mit Inhalt des Overlays
        template<typename Functor>
        void render(Functor &&functor) {
            //was es zu rendern gilt:
            begin();
            functor();
            end();
        }

    private:
        const char *_name;
        bool &_showModal;

        void begin();
        void end();
    };

} // ui_elements

#endif //ATHENA_OVERLAY_HPP
