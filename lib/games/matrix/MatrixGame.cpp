#include "MatrixGame.hpp"
#include "Window.hpp"
#include "InfoBox.hpp"
#include "Fonts.hpp"
#include "TextCentered.hpp"
#include "RandomPicker.hpp"
#include "Centered.hpp"
#include "ColorTheme.hpp"
#include "SoundPolice.hpp"

namespace games {

    MatrixGame::MatrixGame() : Game(abstract_game::GameID::MATRIX) {
        _gameName = "Matrix";
        _gameDescription =
                "Das Spiel 'Matrix' trainiert Konzentrationsfähigkeit und räumliches Vorstellungsvermögen.\n"
                "Für die Arbeit bei Feuerwehr und Polizei ist es essentiell, Aufgaben fokussiert und genau zu lösen.\n"
                "Ein gutes räumliches Vorstellungsvermögen hilft dabei, sich schnell auf Stadt- und Gebäudeplänen \nzu orientieren, "
                "Zugänge zu erkennen und effektive Strategien für Rettungs- oder Einsatzmaßnahmen\nzu entwickeln.\n";
        _gameRules = "Finde jeweils die rotierte bzw. die gespiegelte Version der großen Matrix!\n"
                     "Du hast 2 Minuten Zeit."
                     "Bei einer falschen Antwort werden 10 Sekunden von der Zeit abgezogen.\n";
        _gameControls = "Linke Maustaste: Klicke auf die richtige Matrix in der rechten Spalte.";
        _nMarkedCellsMax = Matrix::getSize() * Matrix::getSize() / 2;
        _nMarkedCellsMin = Matrix::getSize();
    }

    /**
     * @brief displays the startbox, the endbox or the game itself,
     * depending on the game state
     */
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

    /**
     * @brief displays all UI Elements of the running game
     * (timer, matrices, text)
     */
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

    /**
     * @brief displays the question text ("rotiert?" or "gespiegelt?")
     * and the main matrix
     */
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

    /**
     * @brief displays smaller matrices
     * that serve as answer buttons
     */
    void MatrixGame::renderAnswerOptions() {
        float const displayedSize{static_cast<float>(Matrix::getSize() * Matrix::getCellSizeSmall())};
        ImGui::BeginGroup();
        for (int i{0}; i < _matricesToChooseFrom.size(); i++) {
            bool const isCorrect{i == _idOfCorrectMatrix};

            // adjust frame style
            ImGuiStyle &style{ImGui::GetStyle()};
            ImVec2 const oldItemSpacing{style.ItemSpacing};
            style.ItemSpacing = ImVec2(0, 0);
            float const oldFrameRounding{style.FrameRounding};
            style.FrameRounding = 0.f;

            // create transparent button
            ImGui::PushStyleColor(ImGuiCol_Button, commons::Colors::TRANSPARENT);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, commons::Colors::TRANSPARENT);

            ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                  isCorrect ? commons::ColorTheme::SUCCESS_COLOR : commons::ColorTheme::ERROR_COLOR);

            static constexpr float MARGIN{4.f}; // button should overlap matrix a little bit
            std::string const buttonIdString{"buttonForMatrix" + std::to_string(i)};
            if (ImGui::Button(buttonIdString.c_str(), ImVec2(displayedSize + MARGIN, displayedSize + MARGIN))) {
                onClick(isCorrect);
            }
            ImGui::PopStyleColor(3); // pop ImGuiCol_Button(Hovered/Active)

            // display matrix at same position (= covered by transparent button)
            ImVec2 cursorPosition{ImGui::GetCursorPos().x, ImGui::GetCursorPos().y};
            cursorPosition.y -= displayedSize + MARGIN / 2;
            cursorPosition.x += MARGIN / 2;
            ImGui::SetCursorPos(cursorPosition);
            _matricesToChooseFrom[i].renderSmall();
            style.ItemSpacing = oldItemSpacing;
            style.FrameRounding = oldFrameRounding;

            ImGui::NewLine();
            ImGui::NewLine();
        }
        ImGui::EndGroup();
    }

    /**
     * @brief defines the actions that take place
     * when one of the smaller matrices (= answer options) was clicked -
     * depending on whether the answer was correct
     * @param isCorrect
     */
    void MatrixGame::onClick(bool const &isCorrect) {
        if (isCorrect) {
            commons::SoundPolice::safePlaySound(Sound::CORRECT);
            _nCorrectClicksInTotal++;
            _nCorrectClicksSinceLastError++;
            _longestStreak = std::max(_nCorrectClicksSinceLastError, _longestStreak);
            generateNewMatrices();
        } else {
            commons::SoundPolice::safePlaySound(Sound::ERROR);
            _nCorrectClicksSinceLastError = 0;
            _timer.reduceTime(5);
        }
    }

    /**
     * @brief will be called when the timer expires.
     * It will stop the game loop and set the endbox visible.
     */
    void MatrixGame::stop() {
        updateStatistics();
        _endBoxText =
                "Richtige: " + std::to_string(_nCorrectClicksInTotal) + "\nLängster Streak: " +
                std::to_string(_longestStreak);
        _isGameRunning = false;
        _showEndBox = true;
        _endBoxTitle = "Zeit abgelaufen!";
    }

    /**
     * @brief resets the game state, makes the endbox invisible
     * and (re-)starts the timer
     */
    void MatrixGame::start() {
        reset();
        _isGameRunning = true;
        _showEndBox = false;
        _timer.start();
    }

    /**
     * @brief deletes all click records and generates new matrices
     */
    void MatrixGame::reset() {
        _nCorrectClicksSinceLastError = 0;
        _nCorrectClicksInTotal = 0;
        _longestStreak = 0;
        generateNewMatrices();
    }

    /**
     * @brief creates a new main matrix
     * as well as several matrices that serve as answer options.
     * All matrices have the same number of non-empty cells.
     */
    void MatrixGame::generateNewMatrices() {
        _nMarkedCells = commons::RandomPicker::randomInt(_nMarkedCellsMin, _nMarkedCellsMax);
        _mainMatrix.init(_nMarkedCells);
        initMatricesToChooseFrom();
    }

    /**
     * @brief creates several incorrect
     * and one correct matrix as answer options
     */
    void MatrixGame::initMatricesToChooseFrom() {
        _currentGameMode = commons::RandomPicker::pickRandomElement(
                std::vector<GameMode>{GameMode::MIRROR, GameMode::ROTATE});

        // create matrices that are NOT correct
        for (Matrix &matrix: _matricesToChooseFrom) {
            matrix.init(_nMarkedCells);
            while (_currentGameMode == GameMode::MIRROR && matrix.isMirroredVersionOf(_mainMatrix) ||
                   _currentGameMode == GameMode::ROTATE && matrix.isRotatedVersionOf(_mainMatrix)) {
                matrix.init(_nMarkedCells);
            }
        }

        // create one matrix that is mirrored or rotated
        // but still incorrect because it doesn't match _currentGameMode
        // (will overwrite one of the previous incorrect options)
        int const id{commons::RandomPicker::randomInt(0, _matricesToChooseFrom.size() - 1)};
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
        abstract_game::GameSessionManager::getCurrentSession()->addNewGameRunThrough("korrekte Antworten",
                                                                                     _nCorrectClicksInTotal);
    }

} // game
