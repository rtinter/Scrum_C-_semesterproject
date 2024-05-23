#include "imgui.h"

#include <string>
#include <vector>

namespace ui_elements {

    /*************************************************************************************
     * The wrapper class "Window" offers a more convenient and cleaner way of creating
     * new ImGui windows. The default flags for this project are set automatically.
     **************************************************************************************/
    class Window {

    public:
        explicit Window(const char *name, bool *p_open = nullptr,
                        ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar |
                                                 ImGuiWindowFlags_NoDecoration) : _name(name),
                                                                                  _pOpen(p_open),
                                                                                  _flags(flags) {}

        bool begin();

        static void end();

        template<typename Functor>
        void render(Functor &&functor) {
            if (begin()) {
                functor();
                end();
            }
        }

    private:
        const char *_name{};
        bool *_pOpen;
        ImGuiWindowFlags _flags{};
        bool _visible;
    };

}
