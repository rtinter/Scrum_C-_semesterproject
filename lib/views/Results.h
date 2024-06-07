#ifndef ATHENA_RESULTS_H
#define ATHENA_RESULTS_H

#include <string>
#include <vector>
#include <map>
#include "StatisticsGameTable.hpp"
#include "TableContainer.h"

namespace views {

    class Results {

        std::vector<ui_elements::TableContainer> _gameTableContainers; //vector von Table+Überschrift(GameName)
        std::map<int, std::vector<std::string>> _tableNamesAndOrder;
        std::vector<ui_elements::StatisticsGameTable> _gameTables {ui_elements::StatisticsGameTable{_tableNamesAndOrder}};


    public:
        void render();

        void addGameTableContainer(const ui_elements::TableContainer &tableContainer);
        void addGameTableContainers(const std::vector<ui_elements::TableContainer> &tableContainers);

    };

} // views

#endif //ATHENA_RESULTS_H
