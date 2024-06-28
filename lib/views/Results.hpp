#ifndef ATHENA_RESULTS_HPP
#define ATHENA_RESULTS_HPP

#include <string>
#include <vector>
#include <map>
#include "StatisticsGameTable.hpp"
#include "TableContainer.h"

namespace views {

    /***
     * The results page displays the results of all games played.
     * It contains a table for each game, that holds the user data.
     */

    class Results {

        std::vector<ui_elements::TableContainer> _gameTableContainers;
        std::map<int, std::vector<std::string>> _tableNamesAndOrder;
        std::vector<ui_elements::StatisticsGameTable> _gameTables {ui_elements::StatisticsGameTable{_tableNamesAndOrder}};


    public:
        void render();

        void addGameTableContainer(const ui_elements::TableContainer &tableContainer);
        void addGameTableContainers(const std::vector<ui_elements::TableContainer> &tableContainers);

    };

} // views

#endif //ATHENA_RESULTS_HPP