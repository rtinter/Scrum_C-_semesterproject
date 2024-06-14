#include "SimpleMultiplicationTable.hpp"
#include <random>
#include <imgui.h>
#include <chrono>

SimpleMultiplicationTable::SimpleMultiplicationTable()
        : _leftOperand(0), _rightOperand(0), _answer(0), _running(false),
          _completedSuccessfully(false), _difficultyLevel(1) {
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

        ImGui::Text("What is %d * %d?", _leftOperand, _rightOperand);

        static char input[128] = "";
        ImGui::InputText("##input", input, sizeof(input));

        if (ImGui::Button("Submit")) {
            _answer = std::atoi(input);
            _completedSuccessfully = (_answer == _leftOperand * _rightOperand);
            _running = false;
            std::fill(std::begin(input), std::end(input), 0);  // Clear input
        }
    } else {
        ImGui::Text("Press start to begin the task.");
    }
}

void SimpleMultiplicationTable::setDifficulty(int level) {
    _difficultyLevel = level;
}
