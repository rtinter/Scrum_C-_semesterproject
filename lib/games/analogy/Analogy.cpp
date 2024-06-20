#include "Analogy.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


namespace game {

    Analogy::Analogy() : abstract_game::Game(abstract_game::GameID::ANALOGY) {
        _gameName = "Analogy";
        _gameDescription = "Finde die das passende Wort.";
        _gameRules = "1. Analysiere die angezeigte Wortverbindung .\n2. Finde das dazu passende Wort.\n"
                     "3. Bestätige deine Auswahl mit dem Button.\n";
        _gameControls = "Linke Maustaste zur Auswahl der Antwort und ebenfalls zum Bestätigen des Button";

        loadQuestions();
    }

    void Analogy::render() {
        ui_elements::InfoBox(
                _gameID,
                _showStartBox,
                "Startbox",
                _gameName,
                _gameDescription,
                _gameRules,
                _gameControls,
                [this] {
                    start();
                }).render();

        ui_elements::InfoBox(
                _gameID,
                _showEndBox,
                "Endbox",
                _endBoxTitle,
                _endBoxText,
                [this] {
                    reset();
                }).render();

        if (_isGameRunning) {
            renderGame();
        }
    }

    void Analogy::renderGame() {
    }

    void Analogy::loadQuestions() {
        std::ifstream file("questions.json");
        if (file) {
            nlohmann::json data;
            file >> data;
            for (const auto &item: data["questions"]) {
                Question q;
                q.questionText = item["question"];
                q.options['a'] = item["options"]["a"];
                q.options['b'] = item["options"]["b"];
                q.options['c'] = item["options"]["c"];
                q.options['d'] = item["options"]["d"];
                q.correctAnswer = item["correct_answer"].get<char>();
                q.explanation = item["explanation"];
                questions.push_back(q);
            }
        }
    }

    void Analogy::start() {

    }

    void Analogy::stop() {
        Game::stop();
    }

    void Analogy::reset() {

    }

    void Analogy::updateStatistics() {

    }

    std::string Analogy::getName() const {
        return Game::getName();
    };
}