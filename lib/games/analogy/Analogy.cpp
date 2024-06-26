#include "Analogy.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;


namespace game {

    Analogy::Analogy() : abstract_game::Game(abstract_game::GameID::ANALOGY) {
        _gameName = "Analogien";
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
        // Ensure there is at least one question to render
        if (questions.empty()) {
            std::cout << "No questions loaded." << std::endl;
            return;
        }

        ui_elements::Window("Analogien").render([this]() {
            // For simplicity, we will just display the first question in the list
            const Question &currentQuestion = questions.front();

            // Display the question text
            ImGui::Text("%s", currentQuestion.questionText.c_str());

            // Add some spacing
            ImGui::Spacing();
            ImGui::Spacing();

            // Display the answer options as radio buttons
            static char selectedOption = '\0';
            for (const auto &option: currentQuestion.options) {
                std::string label = std::string(1, option.first) + ": " + option.second;
                if (ImGui::RadioButton(label.c_str(), selectedOption == option.first)) {
                    selectedOption = option.first;
                }
            }

            // Add a confirm button
            if (ImGui::Button("Bestätigen")) {
                // Check if the selected option is correct
                if (selectedOption == currentQuestion.correctAnswer) {
                    // Correct answer logic
                    // You can update the game state, show a message, etc.
                    ImGui::Text("Richtige Antwort!");
                } else {
                    // Incorrect answer logic
                    // You can show the correct answer, explanation, etc.
                    ImGui::Text("Falsche Antwort! %s", currentQuestion.explanation.c_str());
                }

                // Reset the selected option for the next question
                selectedOption = '\0';
            }

        });
    }

    void Analogy::loadQuestions() {
        std::fstream file("./config/games/analogy/questionnaire.json");
        if (file) {
            std::cout << "Hat geklappt" << std::endl;
            json data;
            file >> data;

            // Debugging output to check the parsed JSON data
            std::cout << "Parsed JSON data: " << data.dump(4) << std::endl;

            for (const auto &elem: data["questionnaire"]) {
                Question q;
                q.questionText = elem["question"];
                q.options['a'] = elem["options"]["a"];
                q.options['b'] = elem["options"]["b"];
                q.options['c'] = elem["options"]["c"];
                q.options['d'] = elem["options"]["d"];
                q.correctAnswer = elem["correct_answer"].get<std::string>()[0];
                q.explanation = elem["explanation"];
                questions.emplace_back(q);

                // Debugging output to check each loaded question
                std::cout << "Loaded question: " << q.questionText << std::endl;
            }
        } else {
            std::cerr << "Unable to open file questionnaire.json" << std::endl;
        }
    }

    void Analogy::start() {
        _isGameRunning = true;
        _showStartBox = false;
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