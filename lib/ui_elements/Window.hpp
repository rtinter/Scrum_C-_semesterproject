#include "UiElement.hpp"
#include "imgui.h"

#include <string>
#include <vector>

namespace ui_elements {

    class Window {


    public:
        explicit Window(const char *name, bool *p_open = nullptr, ImGuiWindowFlags flags = 0) : _name(name),
                                                                                                _pOpen(p_open),
                                                                                                _flags(flags) {}

        virtual ~Window();

        bool begin();

        static void end();

        template<typename Functor>
        void render(Functor &&functor);

    private:
        const char *_name{};
        bool *_pOpen;
        ImGuiWindowFlags _flags{};
        bool _visible;
    };

}
