//
// Created by zepi on 24.05.24.
//

#ifndef ATHENA_CENTERED_HPP
#define ATHENA_CENTERED_HPP

#include <functional>


namespace ui_elements {
    /**
    * @brief A helper class for centering content within an ImGui window.
    *
    * This class provides a convenient way to center any ImGui content within the current window.
    * It uses ImGui groups and cursor positioning to achieve the centering effect.
    */
    class Centered {
    public:
        /**
        * @brief Centers the content provided by the callback function within the current ImGui window.
        *
        * @param callback A std::function object that contains the ImGui code to be centered.
        *
        * @note This function should be called within an ImGui window context (between ImGui::Begin() and ImGui::End()).
        *       It creates an ImGui group, sets the cursor position to the center of the window, and executes the provided callback function.
        *       The content generated by the callback function will be centered within the window.
        */
        explicit Centered(const std::function<void()>& callback);
    };

} // ui_elements

#endif //ATHENA_CENTERED_HPP
