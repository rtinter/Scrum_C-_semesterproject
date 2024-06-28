#include "AbsurdQuestions.hpp"

namespace game {

    AbsurdQuestions::AbsurdQuestions() : abstract_game::Game(abstract_game::GameID::ABSURD_QUESTIONS) {

    }

    void AbsurdQuestions::loadQuestions() {}

    void AbsurdQuestions::generateRandomQuestion() {}

    void AbsurdQuestions::checkAnswer(bool selectedOption) {}

    void AbsurdQuestions::renderQuestion() {}

    void AbsurdQuestions::renderCorrectMessage() {}

    void AbsurdQuestions::renderGameOver() {}

    void AbsurdQuestions::render() {}

    void AbsurdQuestions::renderGame() {}

    void AbsurdQuestions::start() {}

    void AbsurdQuestions::stop() {}

    void AbsurdQuestions::reset() {}

    void AbsurdQuestions::updateStatistics() {}

    std::string AbsurdQuestions::getName() const { return ""; }

} // namespace game
