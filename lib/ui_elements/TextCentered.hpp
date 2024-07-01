#ifndef ATHENA_TEXTCENTERED_HPP
#define ATHENA_TEXTCENTERED_HPP

#include <string>

namespace ui_elements {

    /**
    * @brief A helper class for rendering centered text in an ImGui window.
    *
    * This class provides a convenient way to display text that is horizontally centered within the current ImGui window.
    * It calculates the appropriate cursor position based on the window width and the size of the text.
    */
    class TextCentered {

    public:
        /**
        * @brief Renders the provided text centered horizontally in the current ImGui window.
        *
        * @param content The null-terminated string containing the text to be rendered.
        *
        * @note This function should be called within an ImGui window context (between ImGui::Begin() and ImGui::End()).
        *       It sets the cursor position and renders the text using ImGui::Text().
        */
        explicit TextCentered(char const *content);

    };

} // ui_elements

#endif //ATHENA_TEXTCENTERED_HPP
