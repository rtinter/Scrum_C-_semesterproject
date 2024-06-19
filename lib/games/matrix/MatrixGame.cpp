#include "MatrixGame.hpp"
#include "Window.hpp"
#include "InfoBox.hpp"
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "RandomPicker.hpp"
#include "Centered.hpp"
#include "ColorTheme.hpp"
#include "SoundManager.hpp"
#include "SoundPolice.hpp"

namespace game {

    MatrixGame::MatrixGame() : Game(abstract_game::GameID::MATRIX) {
        _gameName = "Matrix";
        _gameDescription =
                "Das Spiel 'Matrix' trainiert Konzentrationsfähigkeit und räumliches Vorstellungsvermögen."
                "Für die Arbeit bei Feuerwehr und Polizei ist essentiell, Aufgaben fokussiert und genau zu lösen."
                "Ein gutes räumliches Vorstellungsvermögen hilft dabei, sich schnell auf Stadt- und Gebäudeplänen zu orientieren,"
                "Zugänge zu erkennen und effektive Strategien für Rettungs- oder Einsatzmaßnahmen zu entwickeln.";
        _gameRules = "Finde jeweils die rotierte bzw. die gespiegelte Version der großen Matrix!"
                     "Du hast 2 Minuten Zeit."
                     "Bei einer falschen Antwort werden 10 Sekunden von der Zeit abgezogen.";
        _gameControls = "Linke Maustaste: Klicke auf die richtige Matrix in der rechten Spalte.";
        _nColoredCellsMax = Matrix::getSize() * Matrix::getSize() / 2;
        _nColoredCellsMin = Matrix::getSize();
    }

    /******************************************************************
     * render() displays the startbox, the endbox or the game itself,
     * depending on the game state
     ******************************************************************/
    void MatrixGame::render() {
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

    /*************************************************************
     * renderGame() displays all UI Elements of the running game
     * (timer, matrices, text)
     *************************************************************/
    void MatrixGame::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, commons::Colors::BLACK);
        ui_elements::Window("Matrix Game").render([this] {
            _timer.render();
            ImGui::NewLine();
            renderQuestion();
            ImGui::SameLine(0.f, 200);
            renderAnswerOptions();
            if (_timer.isExpiredNow()) {
                stop();
            }
        });
        ImGui::PopStyleColor(); // pop ImGuiCol_WindowBg
    }

    /****************************************************************************
     * renderQuestion() displays the question text ("rotiert?" or "gespiegelt?")
     * and the main matrix
     ****************************************************************************/
    void MatrixGame::renderQuestion() {
        ImGui::SameLine(0.f, 600);
        ImGui::BeginGroup();
        renderQuestionText();
        ImGui::NewLine();
        _mainMatrix.renderBig();
        ImGui::EndGroup();

    }

    void MatrixGame::renderQuestionText() {
        ImGui::PushStyleColor(ImGuiCol_Text, commons::Colors::BRIGHT_GREEN);
        ImGui::PushFont(commons::Fonts::_matrixFontBig);
        switch (_currentGameMode) {
            case GameMode::ROTATE:
                ImGui::Text("ROTierT?");
                break;
            case GameMode::MIRROR:
                ImGui::Text("GesPiEgelT?");
                break;
        }
        ImGui::PopStyleColor(); // pop ImGuiCol_Text
        ImGui::PopFont();
    }

    /***********************************************
     * renderAnswerOptions displays smaller matrices
     * that serve as answer buttons
     ***********************************************/
    void MatrixGame::renderAnswerOptions() {
        float displayedSize = Matrix::getSize() * Matrix::getCellSizeSmall();
        ImGui::BeginGroup();
        for (int i{0}; i < _matricesToChooseFrom.size(); i++) {
            bool isCorrect{i == _idOfCorrectMatrix};
            // adjust frame style
            ImGuiStyle &style{ImGui::GetStyle()};
            ImVec2 oldItemSpacing{style.ItemSpacing};
            style.ItemSpacing = ImVec2(0, 0);
            float oldFrameRounding{style.FrameRounding};
            style.FrameRounding = 0.f;

            // create transparent button
            ImGui::PushStyleColor(ImGuiCol_Button, commons::Colors::NONE);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, commons::Colors::NONE);

            ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                  isCorrect ? commons::ColorTheme::SUCCESS_COLOR : commons::ColorTheme::ERROR_COLOR);

            float const margin{4.f}; // button should overlap matrix a little bit
            std::string buttonIdString{"buttonForMatrix" + std::to_string(i)};
            if (ImGui::Button(buttonIdString.c_str(), ImVec2(displayedSize + margin, displayedSize + margin))) {
                onClick(isCorrect);
            }
            ImGui::PopStyleColor(3); // pop ImGuiCol_Button(Hovered/Active)

            // display matrix at same position (= covered by transparent button)
            ImVec2 cursorPosition = ImGui::GetCursorPos();
            cursorPosition.y -= displayedSize + margin / 2;
            cursorPosition.x += margin / 2;
            ImGui::SetCursorPos(cursorPosition);
            _matricesToChooseFrom[i].renderSmall();
            style.ItemSpacing = oldItemSpacing;
            style.FrameRounding = oldFrameRounding;

            ImGui::NewLine();
            ImGui::NewLine();
        }
        ImGui::EndGroup();
    }

    /**********************************************************************
     * onClick defines the actions that take place
     * when one of the smaller matrices (= answer options) was clicked -
     * depending on whether the answer was correct
     * @param isCorrect
     **********************************************************************/
    void MatrixGame::onClick(bool const isCorrect) {
        if (isCorrect) {
            commons::SoundPolice::safePlaySound(commons::Sound::CORRECT);
            _nCorrectClicksInTotal++;
            _nCorrectClicksSinceLastError++;
            _longestStreak = std::max(_nCorrectClicksSinceLastError, _longestStreak);
            generateNewMatrices();
        } else {
            commons::SoundPolice::safePlaySound(commons::Sound::ERROR);
            _nCorrectClicksSinceLastError = 0;
            _timer.reduceTime(5);
        }
    }

    /**************************************************************
     * stop() will be called when the timer expires.
     * It will stop the game loop and set the endbox visible.
     ***************************************************************/
    void MatrixGame::stop() {
        _endBoxText =
                "Richtige: " + std::to_string(_nCorrectClicksInTotal) + "\nLängster Streak: " +
                std::to_string(_longestStreak);
        _isGameRunning = false;
        _showEndBox = true;
        _endBoxTitle = "Zeit abgelaufen!";
    }

    /*************************************************************
     * start() resets the game state, makes the endbox invisible
     * and (re-)starts the timer
     *************************************************************/
    void MatrixGame::start() {
        reset();
        _isGameRunning = true;
        _showEndBox = false;
        _timer.start();
    }

    /****************************************************************
     * reset() deletes all click records and generates new matrices
     ****************************************************************/
    void MatrixGame::reset() {
        _nCorrectClicksSinceLastError = 0;
        _nCorrectClicksInTotal = 0;
        _longestStreak = 0;
        generateNewMatrices();
    }

    /***********************************************************
     * generateNewMatrices() creates a new main matrix
     * as well as several matrices that serve as answer options.
     * All matrices have the same number of non-empty cells.
     *************************************************************/
    void MatrixGame::generateNewMatrices() {
        _nColoredCells = commons::RandomPicker::randomInt(_nColoredCellsMin, _nColoredCellsMax);
        _mainMatrix.init(_nColoredCells);
        initMatricesToChooseFrom();
    }

    /******************************************************
     * initMatricesToChooseFrom() creates several incorrect
     * and one correct matrix as answer options
     ******************************************************/
    void MatrixGame::initMatricesToChooseFrom() {
        _currentGameMode = commons::RandomPicker::pickRandomElement(
                std::vector<GameMode>{GameMode::MIRROR, GameMode::ROTATE});

        // create matrices that are NOT correct
        for (Matrix &matrix: _matricesToChooseFrom) {
            matrix.init(_nColoredCells);
            while (_currentGameMode == GameMode::MIRROR && matrix.isMirroredVersionOf(_mainMatrix) ||
                   _currentGameMode == GameMode::ROTATE && matrix.isRotatedVersionOf(_mainMatrix)) {
                matrix.init(_nColoredCells);
            }
        }

        // create one matrix that is mirrored or rotated
        // but still incorrect because it doesn't match _currentGameMode
        // (will overwrite one of the previous incorrect options)
        int id{commons::RandomPicker::randomInt(0, _matricesToChooseFrom.size() - 1)};
        switch (_currentGameMode) {
            case GameMode::ROTATE :
                _matricesToChooseFrom[id] = _mainMatrix.getAMirroredVersion();
                break;
            case GameMode::MIRROR :
                _matricesToChooseFrom[id] = _mainMatrix.getARotatedVersion();
                break;
        }

        // create one correct answer option
        // (will overwrite one of the incorrect options)
        _idOfCorrectMatrix = commons::RandomPicker::randomInt(0, _matricesToChooseFrom.size() - 1);
        switch (_currentGameMode) {
            case GameMode::ROTATE :
                _matricesToChooseFrom[_idOfCorrectMatrix] = _mainMatrix.getARotatedVersion();
                break;
            case GameMode::MIRROR :
                _matricesToChooseFrom[_idOfCorrectMatrix] = _mainMatrix.getAMirroredVersion();
                break;
        }


    }

    void MatrixGame::updateStatistics() {
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("",
                                                                                     _nCorrectClicksInTotal);
    }

} // game