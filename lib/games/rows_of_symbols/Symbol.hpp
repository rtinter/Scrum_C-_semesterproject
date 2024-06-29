#pragma once

#define SYMBOL_SIZE 150.0f // size of a single symbol excluding margin
#define LINE_THICKNESS 8.0f // thickness of the lines in the symbol
#define INNER_GAP 0.16f // gap between the inner and outer shape
#define MARGIN 10.0f // margin around the symbol
#define POINT_OFFSET 0.12f // offset of the points from the center in X and/or Y direction
#define HIGHLIGHT_GREYSCALE 20 // greyscale value for the highlighted symbol
#define HIGHLIGHT_ROUNDING 20.0f // rounding of the highlighted symbol

#include "SymbolType.hpp"
#include "RelativePointPosition.hpp"
#include "imgui.h"

namespace game {
    class Symbol {

        /**
         * Renders the outer circle of the symbol.
         * @param drawList the ImDrawList to render the symbol on
         */
        static void renderOuterCircle(ImDrawList &drawList);

        /**
         * Renders a rectangle as the inner shape of the symbol.
         * @param drawList the ImDrawList to render the symbol on
         */
        static void renderInnerRect(ImDrawList &drawList);

        /**
         * Renders a circle as the inner shape of the symbol.
         * @param drawList the ImDrawList to render the symbol on
         */
        static void renderInnerCircle(ImDrawList &drawList);

        /**
         * Renders a point at the specified position relative to the center of the symbol.
         * @param relativePointPosition the position of the point relative to the center
         * @param drawList the ImDrawList to render the symbol on
         */
        static void renderPoint(RelativePointPosition relativePointPosition, ImDrawList &drawList);

        /**
         * Completes the rendering of the symbol.
         * This method should be called after all parts of the symbol have been rendered.
         */
        static void completeRenderSymbol();

    public:
        /**
         * Renders the specified symbol type.
         * @param symbolType the symbol type to render
         * @param highlighted whether the symbol should be highlighted because it is the current symbol
         */
        static void renderSymbolType(SymbolType symbolType, bool highlighted);
    };
}
