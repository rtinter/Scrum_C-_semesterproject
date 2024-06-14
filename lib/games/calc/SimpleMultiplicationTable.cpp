#include "SimpleMultiplicationTable.hpp"
#include <random>
#include <imgui.h>
#include <chrono>
#include "Fonts.hpp"

SimpleMultiplicationTable::SimpleMultiplicationTable()
        : _leftOperand(0), _rightOperand(0), _answer(0), _running(false),
          _completedSuccessfully(false), _difficultyLevel(1), _focusSet(false) {
    // Seed the random number generator with a combination of random_device and current time
    std::random_device rd;
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto timeSeed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::seed_seq seedSeq{rd(), static_cast<unsigned int>(timeSeed)};
    _rng.seed(seedSeq);
}

void SimpleMultiplicationTable::start() {
    generateTask();
    _running = true;
    _completedSuccessfully = false;
    _focusSet = false; // Reset focus flag at the start of each game
}

bool SimpleMultiplicationTable::isRunning() const {
    return _running;
}

bool SimpleMultiplicationTable::wasSuccessfullyCompleted() const {
    return _completedSuccessfully;
}

void SimpleMultiplicationTable::generateTask() {
    std::uniform_int_distribution<int> dist(1, 10 * _difficultyLevel);
    _leftOperand = dist(_rng);
    _rightOperand = dist(_rng);
}

void SimpleMultiplicationTable::render() {
    if (_running) {
        ImGui::PushFont(commons::Fonts::_header1);

        std::string taskText = std::to_string(_leftOperand) + " * " + std::to_string(_rightOperand) + "?";
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 textSize = ImGui::CalcTextSize(taskText.c_str());

        // Center task text horizontally and vertically
        ImGui::SetCursorPos(ImVec2((windowSize.x - textSize.x) / 2.0f, (windowSize.y - textSize.y) / 3.0f));
        ImGui::Text("%s", taskText.c_str());

        ImGui::PopFont();

        static char input[128] = "";

        if (!_focusSet) {
            ImGui::SetKeyboardFocusHere();
            _focusSet = true; // Focus set once per game session
        }

        // Make input text field shorter and center it
        ImVec2 inputTextSize = ImGui::CalcTextSize(input);
        float inputFieldWidth = 150.0f; // Set desired width
        ImGui::SetCursorPos(ImVec2((windowSize.x - inputFieldWidth) / 2.0f, (windowSize.y - inputTextSize.y) / 2.0f + textSize.y + 50.0f));
        ImGui::SetNextItemWidth(inputFieldWidth); // Set the width of the input field

        if (ImGui::InputText("##input", input, sizeof(input), ImGuiInputTextFlags_EnterReturnsTrue)) {
            _answer = std::atoi(input);
            _completedSuccessfully = (_answer == _leftOperand * _rightOperand);
            _running = false;
            std::fill(std::begin(input), std::end(input), 0);  // Clear input
        }
    }
}

void SimpleMultiplicationTable::setDifficulty(int level) {
    _difficultyLevel = level;
}
