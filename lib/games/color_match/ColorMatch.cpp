#include "ColorMatch.hpp"
#include "../../ui_elements/Window.hpp" // TODO
#include "../../commons/Colors.hpp"

void color_match::ColorMatch::render() {
    bool showGame{true};

    if (showGame) {
        start();
    }
}

void color_match::ColorMatch::start() {

    ImGui::Begin("Color Match Game"); // TODO: use Window class
    ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_Always);

    ImGui::Text("TEst");
    ImGui::Text("TEst");
    ImGui::Text("TEst");
    ImGui::Text("TEst");
    ImGui::Text("TEst");
    ImGui::Text("TEst");

    ImGui::End();


}

void color_match::ColorMatch::reset() {

}
