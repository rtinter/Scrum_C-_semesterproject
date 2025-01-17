#include "Symbol.hpp"

#include <imgui.h>

namespace rows_of_symbols {
    void Symbol::renderSymbolType(SymbolType const symbolType, bool const highlighted) {
        ImDrawList &drawList{*ImGui::GetWindowDrawList()};

        // highlight the symbol if it is the current symbol
        if (highlighted)
            drawList.AddRectFilled(ImGui::GetCursorScreenPos(),
                                   ImVec2(ImGui::GetCursorScreenPos().x + SYMBOL_SIZE + (MARGIN * 2),
                                          ImGui::GetCursorScreenPos().y + SYMBOL_SIZE + (MARGIN * 2)),
                                   IM_COL32(0, 0, 0, HIGHLIGHT_GREYSCALE), HIGHLIGHT_ROUNDING);

        // render the outer circle of the symbol which is needed for all symbol types
        renderOuterCircle(drawList);

        switch (symbolType) {
            case SymbolType::CIRCLE_2_A:
                renderInnerCircle(drawList);
                renderPoint(RelativePointPosition::TOP_LEFT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_RIGHT, drawList);
                break;
            case SymbolType::CIRCLE_2_B:
                renderInnerCircle(drawList);
                renderPoint(RelativePointPosition::TOP_RIGHT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_LEFT, drawList);
                break;
            case SymbolType::CIRCLE_3_A:
                renderInnerCircle(drawList);
                renderPoint(RelativePointPosition::TOP_CENTER, drawList);
                renderPoint(RelativePointPosition::BOTTOM_LEFT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_RIGHT, drawList);
                break;
            case SymbolType::CIRCLE_3_B:
                renderInnerCircle(drawList);
                renderPoint(RelativePointPosition::TOP_LEFT, drawList);
                renderPoint(RelativePointPosition::TOP_RIGHT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_CENTER, drawList);
                break;
            case SymbolType::RECT_2_A:
                renderInnerRect(drawList);
                renderPoint(RelativePointPosition::TOP_LEFT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_RIGHT, drawList);
                break;
            case SymbolType::RECT_2_B:
                renderInnerRect(drawList);
                renderPoint(RelativePointPosition::TOP_RIGHT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_LEFT, drawList);
                break;
            case SymbolType::RECT_3_A:
                renderInnerRect(drawList);
                renderPoint(RelativePointPosition::TOP_CENTER, drawList);
                renderPoint(RelativePointPosition::BOTTOM_LEFT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_RIGHT, drawList);
                break;
            case SymbolType::RECT_3_B:
                renderInnerRect(drawList);
                renderPoint(RelativePointPosition::TOP_LEFT, drawList);
                renderPoint(RelativePointPosition::TOP_RIGHT, drawList);
                renderPoint(RelativePointPosition::BOTTOM_CENTER, drawList);
                break;
            default:
                break;
        }

        // complete the rendering of the symbol
        completeRenderSymbol();
    }

    void Symbol::renderOuterCircle(ImDrawList &drawList) {
        static constexpr ImU32 COLOR_CIRCLE{IM_COL32(205, 0, 0, 255)};
        static constexpr float RADIUS{SYMBOL_SIZE * 0.5f};

        // calculate the center of the circle
        auto const circleCenter{
            ImVec2(ImGui::GetCursorScreenPos().x + (SYMBOL_SIZE * 0.5f) + MARGIN,
                   ImGui::GetCursorScreenPos().y + (SYMBOL_SIZE * 0.5f) + MARGIN)
        };

        // draw the outer circle
        drawList.AddCircle(circleCenter, RADIUS, COLOR_CIRCLE, 0, LINE_THICKNESS);
    }

    void Symbol::renderInnerRect(ImDrawList &drawList) {
        static constexpr ImU32 COLOR_SQUARE{IM_COL32(205, 0, 0, 255)};
        static constexpr auto INGAP{SYMBOL_SIZE * INNER_GAP};

        // calculate the top left and bottom right corner of the inner square
        auto const topLeft{
            ImVec2(ImGui::GetCursorScreenPos().x + INGAP + MARGIN, ImGui::GetCursorScreenPos().y + INGAP + MARGIN)
        };
        auto const bottomRight{
            ImVec2(ImGui::GetCursorScreenPos().x + SYMBOL_SIZE - INGAP + MARGIN,
                   ImGui::GetCursorScreenPos().y + SYMBOL_SIZE - INGAP + MARGIN)
        };

        // draw the inner square
        drawList.AddRect(topLeft, bottomRight, COLOR_SQUARE, 0.f, ImDrawFlags_None, LINE_THICKNESS);
    }

    void Symbol::renderInnerCircle(ImDrawList &drawList) {
        static constexpr ImU32 COLOR_CIRCLE{IM_COL32(205, 0, 0, 255)};
        static constexpr float RADIUS{SYMBOL_SIZE * 0.5f};
        static constexpr float INGAP{SYMBOL_SIZE * INNER_GAP};

        // calculate the center of the circle
        auto const circleCenter{
            ImVec2(ImGui::GetCursorScreenPos().x + (SYMBOL_SIZE * 0.5f) + MARGIN,
                   ImGui::GetCursorScreenPos().y + (SYMBOL_SIZE * 0.5f) + MARGIN)
        };

        // draw the inner circle
        drawList.AddCircle(circleCenter, RADIUS - INGAP, COLOR_CIRCLE, 0, LINE_THICKNESS);
    }

    void Symbol::completeRenderSymbol() {
        // add space for the symbol in the layout
        ImGui::Dummy(ImVec2(SYMBOL_SIZE + (MARGIN * 2), SYMBOL_SIZE + (MARGIN * 2)));

        // add a spacing of 20 pixels between the symbols
        ImGui::SameLine(0.0f, 20.0f);
    }

    void Symbol::renderPoint(RelativePointPosition const relativePointPosition, ImDrawList &drawList) {
        static constexpr ImU32 COLOR{IM_COL32(238, 0, 0, 255)};
        float x{ImGui::GetCursorScreenPos().x + (SYMBOL_SIZE * 0.5f) + MARGIN};
        float y{ImGui::GetCursorScreenPos().y + (150.0f * 0.5f) + MARGIN};

        // calculate the position of the point relative to the center of the symbol
        switch (relativePointPosition) {
            case RelativePointPosition::TOP_LEFT:
                x -= SYMBOL_SIZE * POINT_OFFSET;
                y -= SYMBOL_SIZE * POINT_OFFSET;
                break;
            case RelativePointPosition::TOP_CENTER:
                y -= SYMBOL_SIZE * POINT_OFFSET;
                break;
            case RelativePointPosition::TOP_RIGHT:
                x += SYMBOL_SIZE * POINT_OFFSET;
                y -= SYMBOL_SIZE * POINT_OFFSET;
                break;
            case RelativePointPosition::BOTTOM_LEFT:
                x -= SYMBOL_SIZE * POINT_OFFSET;
                y += SYMBOL_SIZE * POINT_OFFSET;
                break;
            case RelativePointPosition::BOTTOM_CENTER:
                y += SYMBOL_SIZE * POINT_OFFSET;
                break;
            case RelativePointPosition::BOTTOM_RIGHT:
                x += SYMBOL_SIZE * POINT_OFFSET;
                y += SYMBOL_SIZE * POINT_OFFSET;
                break;
        }
        auto const pointPosition{ImVec2(x, y)};

        // draw the point at the calculated position
        drawList.AddCircleFilled(pointPosition, LINE_THICKNESS, COLOR);
    }
} // rows_of_symbols
