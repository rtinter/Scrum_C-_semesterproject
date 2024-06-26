#include "EquationBuilder.hpp"
#include <imgui.h>
#include <string>
#include <algorithm>
#include "Fonts.hpp"
#include "SoundManager.hpp"

EquationBuilder::EquationBuilder() : MathTask(), _targetNumber{0}, _operator{"+"}, _number{0} {
    initializeRNG();
    std::fill(std::begin(_input), std::end(_input), '\0');
}

void EquationBuilder::start() {
    generateTask();
    _running = true;
    _completedSuccessfully = false;
    _focusSet = false;
    std::fill(std::begin(_input), std::end(_input), '\0');
}

bool EquationBuilder::isRunning() const {
    return _running;
}

bool EquationBuilder::wasSuccessfullyCompleted() const {
    return _completedSuccessfully;
}

void EquationBuilder::generateTask() {
    std::uniform_int_distribution<int> numberDist{1, 10};
    std::uniform_int_distribution<int> operatorDist{0, 3};

    int operand1{numberDist(_rng)};
    int operand2{numberDist(_rng)};
    _number = operand1;

    Operator op{static_cast<Operator>(operatorDist(_rng))};

    switch (op) {
        case Operator::ADD:
            _operator = "+";
            _targetNumber = operand1 + operand2;
            break;
        case Operator::SUBTRACT:
            if (operand1 < operand2) std::swap(operand1, operand2);
            _operator = "-";
            _targetNumber = operand1 - operand2;
            break;
        case Operator::MULTIPLY:
            _operator = "*";
            _targetNumber = operand1 * operand2;
            break;
        case Operator::DIVIDE:
            while (operand2 == 0 || operand1 % operand2 != 0 || operand2 == 1) {
                operand2 = numberDist(_rng);
            }
            _operator = "/";
            _targetNumber = operand1 / operand2;
            break;
    }
}

int EquationBuilder::evaluateExpression() const {
    switch (_operator[0]) {
        case '+': return _targetNumber - _number;
        case '-': return _number - _targetNumber;
        case '*': return _targetNumber / _number;
        case '/': return _number / _targetNumber;
        default: return 0;
    }
}

void EquationBuilder::render() {
    if (_running) {
        ImGui::PushFont(commons::Fonts::_header1);

        // Instructions text
        ImGui::PushFont(commons::Fonts::_header3);
        std::string instructionText = "Trage das Ergebnis hier ein und bestätige mit Enter:";
        ImVec2 instructionTextSize = ImGui::CalcTextSize(instructionText.c_str());
        ImGui::PopFont();

        // Calculate dimensions for centering the task
        float inputFieldWidth{100.0f};
        float spaceWidth{ImGui::CalcTextSize(" ").x};
        float numberWidth{ImGui::CalcTextSize(std::to_string(_number).c_str()).x};
        float operatorWidth{ImGui::CalcTextSize(_operator.c_str()).x};
        float targetNumberWidth{ImGui::CalcTextSize(std::to_string(_targetNumber).c_str()).x};
        float equalWidth{ImGui::CalcTextSize("= ").x};
        float totalWidth{numberWidth + spaceWidth + operatorWidth + spaceWidth + inputFieldWidth + spaceWidth + equalWidth + targetNumberWidth};

        ImVec2 windowSize{ImGui::GetWindowSize()};
        float centerX{(windowSize.x - totalWidth) / 2.0f};
        // Calculate the total height for vertical centering
        float textHeight{ImGui::GetTextLineHeight()};
        float totalHeight{textHeight * 2};  // Include space for instructions

        // Position instructions above the task
        ImGui::SetCursorPosY((ImGui::GetWindowHeight() - totalHeight) / 2.0f - textHeight);

        ImGui::PushFont(commons::Fonts::_header3);
        ImGui::SetCursorPosX((ImGui::GetWindowWidth() - instructionTextSize.x) / 2.0f);
        ImGui::Text("%s", instructionText.c_str());
        ImGui::PopFont();

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetTextLineHeight());

        // Center the task horizontally with an offset to the left
        ImGui::SetCursorPosX(centerX - 10);

        // Render the task
        ImGui::AlignTextToFramePadding();
        ImGui::Text("%d", _number);
        ImGui::SameLine();
        ImGui::Text(" %s ", _operator.c_str());
        ImGui::SameLine();
        ImGui::SetNextItemWidth(inputFieldWidth);

        if (!_focusSet) {
            ImGui::SetKeyboardFocusHere();
            _focusSet = true;
        }

        if (ImGui::InputText("##input", _input, IM_ARRAYSIZE(_input), ImGuiInputTextFlags_CharsDecimal | ImGuiInputTextFlags_EnterReturnsTrue)) {
            _completedSuccessfully = evaluateUserInput();
            if (_completedSuccessfully) {
                commons::SoundPolice::safePlaySound(commons::Sound::CORRECT);
            } else {
                commons::SoundPolice::safePlaySound(commons::Sound::ERROR);
            }
            _running = false;
        }

        ImGui::SameLine();
        ImGui::Text("= %d", _targetNumber);

        ImGui::PopFont();
    }
}

bool EquationBuilder::evaluateUserInput() {
    int input{std::atoi(_input)};
    if (_operator == "/" && input == 0) return false; // Avoid division by zero
    return input == evaluateExpression();
}
