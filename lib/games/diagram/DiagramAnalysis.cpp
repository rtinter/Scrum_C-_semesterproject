#include "DiagramAnalysis.hpp"

#include <iostream>

#include "DiagramHelper.hpp"
#include "Fonts.hpp"
#include "GameIDs.hpp"
#include "InfoBox.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "TextCentered.hpp"
#include "Window.hpp"

namespace games {
    DiagramAnalysis::DiagramAnalysis()
            : abstract_game::Game(abstract_game::GameID::DIAGRAM) {
        _gameName = "Diagramm Analyse";
        _gameDescription =
                "Das Ziel von Diagramm-Analyse ist es, die Fähigkeit der Spieler zu verbessern, \n"
                "verschiedene Arten von Diagrammen und Flussdiagrammen schnell und genau zu analysieren. \n"
                "Spieler werden mit verschiedenen Diagrammen konfrontiert und müssen Fragen zu deren Inhalten \n"
                "beantworten, um Punkte zu sammeln.";

        _gameRules = "Wähle die richtige Antwort aus.";

        DiagramHelper helper;
        this->_questions = helper.getQuestions();

        for (auto const &question : this->_questions) {
            sf::Texture txt;
            std::stringstream ss;
            ss << "./assets/games/diagrams/";
            ss << question.image;
            txt.loadFromFile(ss.str());

            this->_textures.insert({question.question, txt});
        }

        _currentQuestion = this->_questions[0];
        for (auto const &qst : _currentQuestion.answers) {
            this->_answers.insert({qst.c_str(), false});
        }
    }

    void DiagramAnalysis::checkAnswers() {
        std::string answer;

        for (auto const &pair : this->_answers) {
            std::string const _answer{pair.first.c_str()};
            if (pair.second) {
                answer = _answer;
                break;
            }
        }

        if (answer == "")
            return;

        if (_currentQuestion.answer.c_str() == answer) {
            _score++;
        }

        if (_currentQuestionIndex + 1 >= _questions.size()) {
            _showEndBox = true;
            updateStatistics();
            return;
        }

        _currentQuestionIndex++;
        _currentQuestion = this->_questions[_currentQuestionIndex];
        _answers.clear();
        for (auto const &qst : _currentQuestion.answers) {
            this->_answers.insert({qst.c_str(), false});
        }
    }

    void DiagramAnalysis::render() {
        ui_elements::InfoBox(_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                             [this] {
                                 start();
                             }).render();
        if(!_isGameRunning)
            return;

        if (_showEndBox && _isGameRunning) {
            std::stringstream ss;
            if(_score > 0){
                ss << "Du hast insgesamt " << _score << " von " << this->_questions.size() << " richtig beantwortet.";
            } else {
                ss << "Du hast keine Fragen richtig beantwortet.";
            }

            _endBoxText = ss.str();
            ui_elements::InfoBox(_gameID, _showEndBox, "Endbox", _endBoxTitle,
                                 _endBoxText, [this] { reset(); })
                    .render();
        } else {
            ui_elements::Window(_gameName).render([this]() {
                if (_questions.empty()) {
                    std::cout << "No questions loaded." << std::endl;
                    return;
                }

                checkAnswers();
                ImGui::PushFont(commons::Fonts::_header2);
                ui_elements::TextCentered(_currentQuestion.question.c_str());

                ImGui::Spacing();
                ImGui::Spacing();

                auto const &qst{this->_textures[_currentQuestion.question]};
                ImGui::Image(qst);

                ImGui::PopFont();
                ImGui::PushFont(commons::Fonts::_body);

                float xOffset{1080 + 100};
                float yOffset{300};
                for (auto const &answer : _currentQuestion.answers) {
                    ImGui::SetCursorPos({xOffset, yOffset});
                    ImGui::Checkbox(answer.c_str(), &_answers[answer]);
                    yOffset += 80;
                }

                ImGui::PopFont();
                ImGui::Spacing();
                ImGui::Spacing();
            });
        }
    }

    void DiagramAnalysis::start() {
        _isGameRunning = true;
    }

    void DiagramAnalysis::renderGame() {}
    void DiagramAnalysis::stop() {
        updateStatistics();
        _isGameRunning = false;
        _showEndBox = true;
    }

    void DiagramAnalysis::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("Richtig", _score);
    }

    void DiagramAnalysis::reset() {
        this->_answers.clear();
        this->_score = 0;
        this->_currentQuestionIndex = 0;
        this->_currentQuestion = this->_questions[0];
        this->_showEndBox = false;
        this->_showStartBox = true;
        this->_isGameRunning = false;
    }

    std::string DiagramAnalysis::getName() const { return _gameName; }
} // namespace games
