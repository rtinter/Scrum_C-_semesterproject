#include "SimpleMultiplicationTable.hpp"
#include <random>
#include <imgui.h>
#include <chrono>
#include "Fonts.hpp"
#include "SoundManager.hpp"

SimpleMultiplicationTable::SimpleMultiplicationTable(int difficultyLevel)
        : _leftOperand(0), _rightOperand(0), _answer(0), _running(false),
          _completedSuccessfully(false), _difficultyLevel(difficultyLevel), _focusSet(false) {
    std::random_device rd;
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto timeSeed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::seed_seq seedSeq{rd(), static_cast<unsigned int>(timeSeed)};
    _rng.seed(seedSeq);
    std::fill(std::begin(_input), std::end(_input), '\0');  // Initialize input
}

void SimpleMultiplicationTable::start() {
    generateTask();
    _running = true;
    _completedSuccessfully = false;
    _focusSet = false; // Reset focus flag at the start of each game
    std::fill(std::begin(_input), std::end(_input), '\0');  // Reset input
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

        std::string taskText = std::to_string(_leftOperand) + " * " + std::to_string(_rightOperand) + " = ";
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 textSize = ImGui::CalcTextSize(taskText.c_str());
        float inputFieldWidth = 150.0f;  // Adjust width for multi-digit numbers
        float spaceWidth = ImGui::CalcTextSize(" ").x;
        float leftOffset = 20.0f;  // Adjust this value to move the task more to the left

        // Calculate total width of the equation to center it
        float totalWidth = textSize.x + spaceWidth + inputFieldWidth;

        // Calculate width of the instructions
        ImGui::PushFont(commons::Fonts::_header3);
        std::string instructionText = "Trage das Ergebnis hier ein und bestätige mit Enter:";
        ImVec2 instructionTextSize = ImGui::CalcTextSize(instructionText.c_str());
        ImGui::PopFont();

        // Calculate the total height for vertical centering
        float textHeight = ImGui::GetTextLineHeight();
        float totalHeight = textHeight * 2;  // Include space for instructions

        // Position instructions above the task
        ImGui::SetCursorPosY((ImGui::GetWindowHeight() - totalHeight) / 2.0f - textHeight);

        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - instructionTextSize.x) / 2.0f);
        ImGui::Text("%s", instructionText.c_str());
        ImGui::PopFont();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + textHeight);

        // Center the task horizontally with an offset to the left
        ImGui::SetCursorPosX(((ImGui::GetWindowWidth() - totalWidth) / 2.0f) - leftOffset);

        // Render the task
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", taskText.c_str());
        ImGui::SameLine();

        if (!_focusSet) {
            ImGui::SetKeyboardFocusHere(); // Set focus to the input field
            _focusSet = true; // Ensure focus is set only once per game session
        }

        ImGui::SetNextItemWidth(inputFieldWidth);
        ImGui::InputText("##input", _input, sizeof(_input), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue);

        ImGui::PopFont();

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter))) {
            _answer = std::atoi(_input);
            _completedSuccessfully = (_answer == _leftOperand * _rightOperand);

            if (_completedSuccessfully) {
                commons::SoundManager::playSound(commons::Sound::CORRECT);
            } else {
                commons::SoundManager::playSound(commons::Sound::ERROR);
            }

            // When we enter input the game/level is finished
            _running = false;

            std::fill(std::begin(_input), std::end(_input), '\0');  // Clear input
        }

        // Show current score and streak (if needed)
        // ImGui::SetCursorPos(ImVec2((windowSize.x - textSize.x) / 2.0f, (windowSize.y - textSize.y) / 1.5f));
    }
}

void SimpleMultiplicationTable::setDifficulty(int level) {
    _difficultyLevel = level;
}
