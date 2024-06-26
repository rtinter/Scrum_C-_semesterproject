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
        ui_elements::Window("Analogien").render([this]() {

            if (_questions.empty()) {
                std::cout << "No questions loaded." << std::endl;
                return;
            }

            if (_showCorrectMessage) {
                auto now = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - _correctMessageStartTime).count();

                if (duration < 3) {
                    ImGui::PushFont(commons::Fonts::_header2);
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ui_elements::TextCentered("Richtige Antwort!");
                    ImGui::PopFont();
                    _solvedText = "Du hast bisher " + std::to_string(_solved) + " Fragen richtig beantwortet";
                    ui_elements::TextCentered(_solvedText.c_str());
                    ImGui::Spacing();
                    ui_elements::TextCentered(" Weiter so!");

                    return;
                } else {
                    _showCorrectMessage = false;
                    generateRandomQuestion();
                }
            }


            ImGui::Text("%s", _currentQuestion.questionText.c_str());

            ImGui::Spacing();
            ImGui::Spacing();

            static char selectedOption = '\0';
            for (const auto &option : _currentQuestion.options) {
                std::string label = std::string(1, option.first) + " : " + option.second;
                if (ImGui::RadioButton(label.c_str(), selectedOption == option.first)) {
                    selectedOption = option.first;
                }
            }

            if (ImGui::Button("Bestätigen")) {
                if (selectedOption == _currentQuestion.correctAnswer) {
                    _solved++;
                    _showCorrectMessage = true;
                    _correctMessageStartTime = std::chrono::steady_clock::now();
                } else {
                    ImGui::Text("Falsche Antwort! %s", _currentQuestion.explanation.c_str());
                    stop();

                    _endBoxTitle = "Das war leider nicht korrekt";
                    _endBoxText = "Du hast diesmal " + std::to_string(_solved) + " in Folge lösen können \n" +
                            "Die Lösung der letzten Aufgabe lautet:" + _currentQuestion.explanation;
                }
            }
        });
    }

    void Analogy::loadQuestions() {
        std::fstream file("./config/games/analogy/questionnaire.json");
        if (file) {
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
                _questions.emplace_back(q);

                // Debugging output to check each loaded question
                std::cout << "Loaded question: " << q.questionText << std::endl;
            }
        } else {
            std::cerr << "Unable to open file questionnaire.json" << std::endl;
        }
    }

    void Analogy::generateRandomQuestion() {
        if (!_questions.empty()) {
            _currentQuestion = commons::RandomPicker::pickRandomElement(_questions);
        }
    }


    void Analogy::start() {
        _solved = 0;
        generateRandomQuestion();
        _isGameRunning = true;
        _showEndBox = false;
        _showStartBox = false;
    }

    void Analogy::stop() {
        updateStatistics();
        _isGameRunning = false;
        _showEndBox = true;
    }

    void Analogy::reset() {
        start();
    }

    void Analogy::updateStatistics() {

    }

    std::string Analogy::getName() const {
        return Game::getName();
    };
}