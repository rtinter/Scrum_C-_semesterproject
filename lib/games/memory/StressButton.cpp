#include "StressButton.hpp"
#include "MemoryTile.hpp"
#include <imgui.h>
#include <random>
#include <cmath>

namespace memory {

    StressButton::StressButton() {
        updateNextSpawnInterval();
    }

    void StressButton::update() {
        auto now = std::chrono::steady_clock::now();
        if (!_visible) {
            // Check if the elapsed time since the last disappearance is greater than the next spawn interval
            if (std::chrono::duration_cast<std::chrono::seconds>(now - _disappearTime) >= _nextSpawnInterval) {
                spawn();
            }
        } else {
            if (now >= _disappearTime) {
                _visible = false;
                _clicked = false;
                updateNextSpawnInterval();
            }
        }
    }

    void StressButton::render() {
        if (_visible) {
            ImGui::SetCursorPos(_stressButtonPosition);
            ImGui::PushStyleColor(ImGuiCol_Button, _clicked ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1));
            if (!_clicked) {
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.5f, 0.5f, 1.0f));
            } else {
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 1, 0, 1));
            }
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0, 0, 1));
            ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 1));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

            ImVec2 textSize = ImGui::CalcTextSize("Click");
            ImVec2 textPos = ImVec2(
                    (_stressButtonSize.x - textSize.x) / 2.0f,
                    (_stressButtonSize.y - textSize.y) / 2.0f
            );

            ImGui::SetCursorPos(ImVec2(_stressButtonPosition.x + textPos.x, _stressButtonPosition.y + textPos.y));
            if (ImGui::Button("Click##StressButton", _stressButtonSize)) {
                _clickCount++;
                _clicked = true;
            }
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(4);
        }
    }

    void StressButton::spawn() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> disX(0.0f, ImGui::GetWindowWidth() - _stressButtonSize.x);
        std::uniform_real_distribution<float> disY(0.0f, ImGui::GetWindowHeight() - _stressButtonSize.y);

        // Calculate the bounding box for the tile formation
        float minX{std::numeric_limits<float>::max()};
        float minY{std::numeric_limits<float>::max()};
        float maxX{std::numeric_limits<float>::min()};
        float maxY{std::numeric_limits<float>::min()};

        for (const auto &coord: _tiles) {
            minX = std::min(minX, coord->getPosition().x);
            minY = std::min(minY, coord->getPosition().y);
            maxX = std::max(maxX, coord->getPosition().x + _tileSize.x);
            maxY = std::max(maxY, coord->getPosition().y + _tileSize.y);
        }

        bool validPosition{false};

        while (!validPosition) {
            _stressButtonPosition = {disX(gen), disY(gen)};
            // Ensure the button does not spawn within the bounding box of the tiles
            validPosition = (_stressButtonPosition.x + _stressButtonSize.x < minX || _stressButtonPosition.x > maxX
                             || _stressButtonPosition.y + _stressButtonSize.y < minY || _stressButtonPosition.y > maxY);
        }

        _visible = true;
        _spawnTime = std::chrono::steady_clock::now();
        _disappearTime = _spawnTime + std::chrono::seconds(2); // Stays visible for 2 seconds
        _totalCount++;
    }

    void StressButton::setTileData(std::vector<std::shared_ptr<MemoryTile>> const &tiles, ImVec2 const &tileSize) {
        _tiles = tiles;
        _tileSize = tileSize;
    }

    void StressButton::updateNextSpawnInterval() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(5, 15); // Random interval between 5 and 15 seconds
        _nextSpawnInterval = std::chrono::seconds(dis(gen));
    }

    void StressButton::reset() {
        _visible = false;
        _clickCount = 0;
        _totalCount = 0;
        _clicked = false;
        _disappearTime = std::chrono::steady_clock::now();
        updateNextSpawnInterval();
    }


    int StressButton::getClickCount() const {
        return _clickCount;
    }

    int StressButton::getTotalCount() const {
        return _totalCount;
    }

} // namespace memory
