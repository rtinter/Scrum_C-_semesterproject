#pragma once

#include <map>
#include <string>
#include <vector>

#include "StatisticsGameTable.hpp"
#include "TableContainer.hpp"

namespace views {
    /***
     * The results page displays the results of all games played.
     * It contains a table for each game, that holds the user data.
     */
    class Results {
        std::vector<ui_elements::TableContainer> _gameTableContainers;
        std::map<int, std::vector<std::string> > _tableNamesAndOrder;
        std::vector<ui_elements::StatisticsGameTable> _gameTables{
            ui_elements::StatisticsGameTable{_tableNamesAndOrder}
        };

    public:
        void render();

        void addGameTableContainer(ui_elements::TableContainer const &tableContainer);
    };
} // views
