#ifndef ATHENA_TABLECONTAINER_HPP
#define ATHENA_TABLECONTAINER_HPP

#include "UiElement.hpp"
#include "StatisticsGameTable.hpp"
#include <string>

namespace ui_elements {
/**
 * On the results page you got a table for each game, that holds the user data.
 * This class creates a container to hold the table + additional info and the required styling of one such container.
 */
class TableContainer : public ui_elements::UiElement {

private:
    std::string _gameName;
    StatisticsGameTable _statisticsGameTable;

public:
    explicit TableContainer(std::string const &gameName, StatisticsGameTable const &statisticsGameTable);

    void render() override;


    };

} // ui_elements

#endif //ATHENA_TABLECONTAINER_HPP
