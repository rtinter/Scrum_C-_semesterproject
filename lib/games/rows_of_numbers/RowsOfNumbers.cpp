//
// Created by jane on 14.06.24.
//

#include "RowsOfNumbers.hpp"
#include <InfoBox.hpp>
#include <Window.hpp>
#include <Fonts.hpp>
#include <TextCentered.hpp>

namespace game {
    RowsOfNumbers::RowsOfNumbers() : abstract_game::Game(abstract_game::GameID::ROWS_OF_NUMBERS) {
        _gameName = "Zahlenreihen";
        _gameDescription = "Finde die fehlende Zahl in der Zahlenreihe.";
        _gameRules = "Tippe die fehlende Zahl der Zahlenreihe in das Eingabefeld.";
        _gameControls = "Tippe die fehlende Zahl der Zahlenreihe in das Eingabefeld.";
    }

    void RowsOfNumbers::render() {
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

    void RowsOfNumbers::renderGame() {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, _windowColor);

        ui_elements::Window("Zahlenreihen").render([]() {

            ImGui::Spacing();

            ImGui::PushFont(commons::Fonts::_header1);
            ui_elements::TextCentered("1 2 3 4 5 6 7 8 9 10");
            ImGui::PopFont();

            ImGui::PushFont(commons::Fonts::_header2);
            ui_elements::TextCentered("Füge die fehlende Zahl ein:");
            ImGui::PopFont();
        });

        ImGui::PopStyleColor();
    }

    void RowsOfNumbers::start() {
        _isGameRunning = true;
        _showEndBox = false;

        _windowColor = commons::Colors::LIGHT_GRAY;
    }

    void RowsOfNumbers::reset() {

    }

    void RowsOfNumbers::updateStatistics() {

    }

    void RowsOfNumbers::stop() {
        _isGameRunning = false;
    }

    std::string RowsOfNumbers::getName() const {
        return Game::getName();
    }

    RowsOfNumbers::~RowsOfNumbers() {

    }


} // game