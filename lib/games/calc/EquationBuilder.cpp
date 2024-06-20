#include "EquationBuilder.hpp"
#include <imgui.h>
#include <chrono>
#include <string>
#include <algorithm>
#include "Fonts.hpp"
#include "SoundManager.hpp"

EquationBuilder::EquationBuilder(int difficultyLevel)
        : _targetNumber(0), _running(false),
          _completedSuccessfully(false), _difficultyLevel(difficultyLevel), _focusSet(false) {
    std::random_device rd;
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto timeSeed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::seed_seq seedSeq{rd(), static_cast<unsigned int>(timeSeed)};
    _rng.seed(seedSeq);
}

void EquationBuilder::start() {
    generateTask();
    _running = true;
    _completedSuccessfully = false;
    _focusSet = false; // Reset focus flag at the start of each game
    _inputBuffers = std::vector<std::string>(_difficultyLevel, std::string(10, '\0')); // Reset input buffers
}

bool EquationBuilder::isRunning() const {
    return _running;
}

bool EquationBuilder::wasSuccessfullyCompleted() const {
    return _completedSuccessfully;
}

void EquationBuilder::generateTask() {
    std::uniform_int_distribution<int> numberDist(1, 10 * _difficultyLevel);
    std::uniform_int_distribution<int> operatorDist(0, 3); // 0: +, 1: -, 2: *, 3: /

    do {
        _numbers.clear();
        _operators.clear();

        for (int i = 0; i < _difficultyLevel + 1; ++i) {
            _numbers.push_back(numberDist(_rng));
            if (i < _difficultyLevel) {
                switch (operatorDist(_rng)) {
                    case 0: _operators.push_back("+"); break;
                    case 1: _operators.push_back("-"); break;
                    case 2: _operators.push_back("*"); break;
                    case 3: _operators.push_back("/"); break;
                }
            }
        }

        _targetNumber = evaluateExpression();

    } while (!isSolvable());
}

bool EquationBuilder::isSolvable() const {
    // Ensure that the expression is valid and the result is non-zero for division
    if (_targetNumber == 0) return false;
    for (int i = 0; i < _difficultyLevel; ++i) {
        if (_operators[i] == "/" && (_numbers[i + 1] == 0 || _numbers[i] % _numbers[i + 1] != 0)) {
            return false;
        }
    }
    return true;
}

int EquationBuilder::evaluateExpression() const {
    // Evaluate the expression while considering operator precedence
    std::vector<int> values = _numbers;
    std::vector<std::string> ops = _operators;

    // First pass for * and /
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == "*" || ops[i] == "/") {
            int left = values[i];
            int right = values[i + 1];
            int result = (ops[i] == "*") ? left * right : left / right;
            values[i] = result;
            values.erase(values.begin() + i + 1);
            ops.erase(ops.begin() + i);
            --i;
        }
    }

    // Second pass for + and -
    int result = values[0];
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == "+") {
            result += values[i + 1];
        } else if (ops[i] == "-") {
            result -= values[i + 1];
        }
    }
    return result;
}

void EquationBuilder::render() {
    if (_running) {
        ImGui::PushFont(commons::Fonts::_header1);

        float inputFieldWidth = 100.0f;  // Adjust width for multi-digit numbers
        float textHeight = ImGui::GetTextLineHeight();
        float spaceWidth = ImGui::CalcTextSize(" ").x;
        float leftOffset = 20.0f;  // Adjust this value to move the task more to the left

        // Calculate total width of the equation to center it
        float totalWidth = 0.0f;
        totalWidth += ImGui::CalcTextSize(std::to_string(_numbers[0]).c_str()).x;
        for (int i = 0; i < _difficultyLevel; ++i) {
            totalWidth += spaceWidth;
            totalWidth += ImGui::CalcTextSize(_operators[i].c_str()).x;
            totalWidth += spaceWidth;
            totalWidth += inputFieldWidth;
        }
        totalWidth += spaceWidth;
        totalWidth += ImGui::CalcTextSize("= ").x;
        totalWidth += ImGui::CalcTextSize(std::to_string(_targetNumber).c_str()).x;

        // Calculate width of the instructions
        ImGui::PushFont(commons::Fonts::_header3);
        std::string instructionText = "Füllen Sie die Lücken aus und drücken Sie Enter:";
        ImVec2 instructionTextSize = ImGui::CalcTextSize(instructionText.c_str());
        ImGui::PopFont();

        // Calculate the total height for vertical centering
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
        ImGui::Text("%s", std::to_string(_numbers[0]).c_str());
        ImGui::SameLine();

        for (int i = 0; i < _difficultyLevel; ++i) {
            ImGui::AlignTextToFramePadding();
            ImGui::Text(" %s ", _operators[i].c_str());
            ImGui::SameLine();
            ImGui::SetNextItemWidth(inputFieldWidth);

            if (!_focusSet) {
                ImGui::SetKeyboardFocusHere(); // Set focus to the first input field
                _focusSet = true; // Ensure focus is set only once per game session
            }

            ImGui::InputText((std::string("##input") + std::to_string(i)).c_str(), &_inputBuffers[i][0], _inputBuffers[i].size(), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::SameLine();
        }

        ImGui::AlignTextToFramePadding();
        ImGui::Text("= %d", _targetNumber);

        ImGui::PopFont();

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Enter))) {
            _completedSuccessfully = evaluateUserInput();
            if (_completedSuccessfully) {
                commons::SoundManager::playSound(commons::Sound::CORRECT);
            } else {
                commons::SoundManager::playSound(commons::Sound::ERROR);
            }

            // When we submit input the game/level is finished
            _running = false;
        }
    }
}


bool EquationBuilder::evaluateUserInput() {
    int result = _numbers[0];
    for (int i = 0; i < _difficultyLevel; ++i) {
        int nextNumber = std::atoi(&_inputBuffers[i][0]);
        if (_operators[i] == "+") result += nextNumber;
        else if (_operators[i] == "-") result -= nextNumber;
        else if (_operators[i] == "*") result *= nextNumber;
        else if (_operators[i] == "/") {
            if (nextNumber != 0) {
                result /= nextNumber;
            }
        }
    }
    return result == _targetNumber;
}

void EquationBuilder::setDifficulty(int level) {
    _difficultyLevel = level;
}
