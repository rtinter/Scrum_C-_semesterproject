#include "Sequence.hpp"
#include "Fonts.hpp"
#include "ColorTheme.hpp"
#include "InfoBox.hpp"
#include "TextCentered.hpp"
#include "Window.hpp"
#include "Centered.hpp"
#include "SoundPolice.hpp"
#include <algorithm>
#include <random>
#include <thread>

namespace sequence {

    Sequence::Sequence() : Game(abstract_game::GameID::SEQUENCE) {
        _gameName = "Abfolge-Merken-Spiel";
        _gameDescription = "Unser Abfolge-Merken-Spiel soll die Fähigkeit testen, sich Abfolgen einzuprägen\nund korrekt wiederzugeben.\n";
        _gameRules = "Auf dem Bildschirm werden 9 verschiedene Buttons angezeigt.\n"
                     "Diese Buttons werden nacheinander aufleuchten und anschließend müssen die Buttons in exakt dieser\n"
                     "Reihenfolge angeklickt werden. Die Abfolge muss also wiederholt werden.\n"
                     "Die Abfolge wird schrittweise ausgegeben. Also erst nur ein Button, dann zwei, dann drei usw.\n"
                     "Teste deine Fähigkeiten und schaue, wie weit du kommst!\n";
        _gameControls = "Linke Maustaste: Klicken der Buttons in der korrekten Reihenfolge.\n";
    }

    void Sequence::render() {
        ui_elements::InfoBox(_gameID, _showStartBox, "Startbox", _gameName, _gameDescription, _gameRules, _gameControls,
                             [this] {
                                 start();
                             }).render();

        ui_elements::InfoBox(_gameID, _showEndBox, "Endbox", _endBoxTitle, _endBoxText, [this] {
            start();
        }).render();

        if (_isGameRunning) {
            renderGame();
        }

    }

    void Sequence::renderGame() {
        ui_elements::Window("Sequence Game").render(([this] {

            ui_elements::Centered(true, true, [this] {
                ImGui::PushFont(commons::Fonts::_header3);
                switch (_currentGameMode) {
                    case GameMode::WATCH:
                        ImGui::Text("Sieh zu und versuch dir die Reihenfolge zu merken!");
                        break;
                    case GameMode::REPEAT:
                        ImGui::Text("Wiederhole die Reihenfolge!");
                        break;
                }
                ImGui::PopFont();

                displayButtons();
            });
        }));

    }

    void Sequence::start() {
        _currentGameMode = GameMode::WATCH;
        _isGameRunning = true;
        _showEndBox = false;
        _sequenceButtonIterator = 0;
        _wasLastButtonOfSequence = false;

        _levelCounter = 0;
        _buttonsClickedSequence.clear();
        //Set all button states to false/0 (not lighting up)
        _buttonStates.fill(0);

        chooseNextRandomButton();
        nextLevel();        //first level
        showSequence();

    }

    void Sequence::reset() {
        start();
    }

    void Sequence::stop() {
        updateStatistics();
        _endBoxString = "Du hast eine Abfolge von " + std::to_string(_longestReproducedSequence) +
                        " Klicks richtig wiederholt!";
        _endBoxText = _endBoxString;
        _isGameRunning = false;
        _showEndBox = true;
        _endBoxTitle = "Falsch geklickt!";
    }

    void Sequence::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten in Folge",
                                                                                     _longestReproducedSequence);
    }

    void Sequence::displayButtons() {


        ImGui::NewLine();


        for (int i{1}; i <= _NUMBER_OF_BUTTONS; i++) {
            int buttonID{i - 1};

            if ((i - 1) % 3) {
                ImGui::SameLine();
            } else {
                ImGui::NewLine();
            }
            switch (_currentGameMode) {
                case GameMode::WATCH:

                    checkWaitTimeExpired();
                    checkLitUpExpired(
                            _buttonStates[buttonID]);       //check, if Button is currently already lit up and then should be turned off
                    if (_wasLastButtonOfSequence) {
                        switchGameMode();
                    }

                    if (_buttonStates[buttonID]) {        //button is supposed to light up -> light button up by pushing accentColor
                        ImGui::PushStyleColor(ImGuiCol_Button, commons::ColorTheme::ACCENT_COLOR);
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, commons::ColorTheme::ACCENT_COLOR);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, commons::ColorTheme::ACCENT_COLOR);
                        ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::TRANSPARENT);
                    } else {                            //button is not supposed to light up -> normal render color
                        ImGui::PushStyleColor(ImGuiCol_Button, commons::ColorTheme::PRIMARY_COLOR);
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, commons::ColorTheme::PRIMARY_COLOR);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, commons::ColorTheme::PRIMARY_COLOR);
                        ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::TRANSPARENT);
                    }

                    if (ImGui::Button(std::to_string(buttonID).c_str(), ImVec2(200, 200))) {
                        //clicking is not supposed to have any effect in WATCH mode
                    }

                    ImGui::PopStyleColor(); //one time extra because of Hovered color

                    break;
                case GameMode::REPEAT:

                    ImGui::PushStyleColor(ImGuiCol_Button, commons::ColorTheme::PRIMARY_COLOR);
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, commons::ColorTheme::SECONDARY_COLOR);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 0));

                    if (ImGui::Button(std::to_string(buttonID).c_str(), ImVec2(200, 200))) {
                        isClickedInCorrectOrder(buttonID);
                    }

                    break;

            }

            ImGui::PopStyleColor(3);
        }

    }

    void Sequence::isClickedInCorrectOrder(int const &buttonID) {

        if (buttonID ==
            _buttonsClickedSequence[_sequenceButtonIterator]) {     //if clicked button is the right button to be clicked in sequence
            _correctClicksOfCurrentSequence++;
            playButtonSound(buttonID);
            _sequenceButtonIterator++;  //make sure that the next button in line gets rated as correct now!
            if (_correctClicksOfCurrentSequence == _levelCounter) {
                //go to next level and switch back to watch gamemode
                _longestReproducedSequence = _correctClicksOfCurrentSequence;
                nextLevel();
                switchGameMode();
            }

        } else {
            commons::SoundPolice::safePlaySound(commons::Sound::BEEP_FAIL);
            stop();     //wrong button clicked -> GAMEOVER!
        }

    }

    void Sequence::chooseNextRandomButton() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribution(0, _NUMBER_OF_BUTTONS - 1);

        _buttonsClickedSequence.emplace_back(distribution(gen));
    }

    void Sequence::showSequence() {
        int buttonForLoopIteration{0};  //to keep iterator of button in sequence in sync with the sequence displayed
        for (int button: _buttonsClickedSequence) {
            if ((_buttonStates[button] == 0) &&
                _canShowNextButtonInSequence && (_sequenceButtonIterator ==
                                                 buttonForLoopIteration) &&
                !_mustWait) {        //if chosen button is not yet lit up AND no other button is currently lit up AND wait time between light ups is over, light it up!
                lightUp(_buttonStates[button], button);    //light up button X by setting state of button X to 1/true
            }
            buttonForLoopIteration++;

        }
    }

    void Sequence::lightUp(int &buttonState, int const &buttonID) {
        //Sets a button to be lit up for 800ms
        _stopHighlightingHere =
                std::chrono::steady_clock::now() + std::chrono::milliseconds(_lightUpDurationInMilliseconds);
        buttonState = 1;
        playButtonSound(buttonID);
        _canShowNextButtonInSequence = false;   //another button is currently lit up, this variable assures no other button is being lit up at the same time
    }

    void Sequence::checkLitUpExpired(int &buttonState) {

        //if Lighting up time is expired
        if ((buttonState == 1) && std::chrono::steady_clock::now() > _stopHighlightingHere) {
            buttonState = 0;
            waitInBetweenButtons();

        }
    }

    /**
     * Set up LevelCounter -> max sequence length if player correctly reproduces sequence
     */
    void Sequence::nextLevel() {
        _levelCounter++;
    }

    /**
     * Switches GameMode from WATCH to REPEAT and vice versa.
     */
    void Sequence::switchGameMode() {
        switch (_currentGameMode) {
            case GameMode::WATCH:
                _currentGameMode = GameMode::REPEAT;

                _correctClicksOfCurrentSequence = 0; //reset correctClicksCount for the new round
                _sequenceButtonIterator = 0;
                break;

            case GameMode::REPEAT:
                _currentGameMode = GameMode::WATCH;;

                std::this_thread::sleep_for(std::chrono::milliseconds(700));
                _wasLastButtonOfSequence = false; //reset sequence show endtime checker variable
                _sequenceButtonIterator = 0;
                chooseNextRandomButton(); //Sequence must be elongated by one button click

                showSequence();
                break;
        }
    }

    void Sequence::moveOnToNextButton() {
        _sequenceButtonIterator++;
    }

    void Sequence::waitInBetweenButtons() {
        _stopWaitingHere = std::chrono::steady_clock::now() + std::chrono::milliseconds(_waitDurationInMilliseconds);
        _mustWait = true;
    }

    void Sequence::checkWaitTimeExpired() {
        if (_mustWait && (std::chrono::steady_clock::now() > _stopWaitingHere)) {
            _mustWait = false;

            if (_sequenceButtonIterator <= _levelCounter) {

                _canShowNextButtonInSequence = true;    //Button ist wieder aus, also kann nun der nächste Button aufleuchten
                moveOnToNextButton();
                showSequence();
                if (_sequenceButtonIterator == _levelCounter) {
                    _wasLastButtonOfSequence = true;
                }
            }
        }
    }

    void Sequence::playButtonSound(const int &buttonID) {
        switch (buttonID) {
            case 0:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 0.666f);
                break;
            case 1:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 0.777f);
                break;
            case 2:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 0.888f);
                break;
            case 3:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 0.999f);
                break;
            case 4:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 1.11f);
                break;
            case 5:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 1.222f);
                break;
            case 6:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 1.333f);
                break;
            case 7:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 1.444f);
                break;
            case 8:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 1.555f);
                break;
            default:
                commons::SoundPolice::safePlaySound(commons::Sound::BEEP, 100, 1.0f);
                break;

        }
    }
} // sequence
