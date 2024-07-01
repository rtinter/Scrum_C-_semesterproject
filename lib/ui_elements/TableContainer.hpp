#pragma once

#include <string>

#include "StatisticsGameTable.hpp"
#include "UiElement.hpp"

namespace ui_elements {
    /**
     * On the results page you got a table for each game, that holds the user data.
     * This class creates a container to hold the table + additional info and the required styling of one such container.
     */
    class TableContainer final : public ui_elements::UiElement {
        std::string _gameName;
        StatisticsGameTable _statisticsGameTable;

    public:
        explicit TableContainer(std::string const &gameName, StatisticsGameTable const &statisticsGameTable);

        void render() override;
    };
} // ui_elements
