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

        // Calculate target number and ensure the equation is solvable
        _targetNumber = _numbers[0];
        for (int i = 0; i < _difficultyLevel; ++i) {
            if (_operators[i] == "+") _targetNumber += _numbers[i + 1];
            else if (_operators[i] == "-") _targetNumber -= _numbers[i + 1];
            else if (_operators[i] == "*") _targetNumber *= _numbers[i + 1];
            else if (_operators[i] == "/") {
                if (_numbers[i + 1] != 0) { // Avoid division by zero
                    _targetNumber /= _numbers[i + 1];
                }
            }
        }
    } while (!isSolvable());
}

bool EquationBuilder::isSolvable() const {
    if (_targetNumber == 0) return false;  // Avoid zero result for division
    for (int i = 0; i < _difficultyLevel; ++i) {
        if (_operators[i] == "/" && (_numbers[i + 1] == 0 || _targetNumber == 0)) {
            return false; // Division by zero is not solvable, avoid zero result
        }
        if (_operators[i] == "/" && _numbers[i] % _numbers[i + 1] != 0) {
            return false; // Ensure the division results in an integer
        }
    }
    return true;
}

void EquationBuilder::render() {
    if (_running) {
        ImGui::PushFont(commons::Fonts::_header1);

        float inputFieldWidth = 100.0f;  // Increase width for multi-digit numbers
        float textHeight = ImGui::GetTextLineHeight();

        // Calculate total width of the equation to center it
        float totalWidth = ImGui::CalcTextSize(std::to_string(_numbers[0]).c_str()).x;
        for (int i = 0; i < _difficultyLevel; ++i) {
            totalWidth += ImGui::CalcTextSize((" " + _operators[i] + " _").c_str()).x;
            totalWidth += inputFieldWidth - ImGui::CalcTextSize("_").x;  // Account for input field width
        }
        totalWidth += ImGui::CalcTextSize((" = " + std::to_string(_targetNumber)).c_str()).x;

        // Calculate the total height for vertical centering
        float totalHeight = textHeight;

        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - totalWidth) / 2.0f);
        ImGui::SetCursorPosY((ImGui::GetWindowHeight() - totalHeight) / 2.0f);

        ImGui::AlignTextToFramePadding();
        ImGui::Text("%s", std::to_string(_numbers[0]).c_str());
        ImGui::SameLine();

        for (int i = 0; i < _difficultyLevel; ++i) {
            ImGui::AlignTextToFramePadding();
            ImGui::Text(" %s ", _operators[i].c_str());
            ImGui::SameLine();
            ImGui::SetNextItemWidth(inputFieldWidth);
            ImGui::AlignTextToFramePadding();
            ImGui::InputText((std::string("##input") + std::to_string(i)).c_str(), &_inputBuffers[i][0], _inputBuffers[i].size(), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::SameLine();
        }

        ImGui::AlignTextToFramePadding();
        ImGui::Text(" = %d", _targetNumber);

        ImGui::PopFont();

        ImGui::PushFont(commons::Fonts::_header3);
        std::string instructionText = "Fill in the blanks and press Enter:";
        ImVec2 instructionTextSize = ImGui::CalcTextSize(instructionText.c_str());
        ImGui::SetCursorPos(ImVec2((ImGui::GetWindowWidth() - instructionTextSize.x) / 2.0f, (ImGui::GetWindowHeight() - instructionTextSize.y) / 2.0f + textHeight));
        ImGui::Text("%s", instructionText.c_str());
        ImGui::PopFont();

        if (!_focusSet) {
            ImGui::SetKeyboardFocusHere();
            _focusSet = true; // Focus set once per game session
        }

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
