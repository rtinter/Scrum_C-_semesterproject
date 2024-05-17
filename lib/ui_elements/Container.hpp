#include "UiElement.hpp"
#include "vector"

namespace ui_elements {

    class Container : UiElement{

        std::vector<UiElement> uiElements;

        void render() override;

    };

}
