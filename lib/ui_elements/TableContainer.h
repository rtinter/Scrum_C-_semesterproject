//
// Created by samtf on 07.06.2024.
//

#ifndef ATHENA_TABLECONTAINER_H
#define ATHENA_TABLECONTAINER_H

#include "UiElement.hpp"
#include "StatisticsGameTable.hpp"
#include <string>

namespace ui_elements {

class TableContainer : public ui_elements::UiElement {

private:
    float _height {600.0f};
    float _width {700.0f};
    std::string _gameName;
    StatisticsGameTable _statisticsGameTable;

public:
    explicit TableContainer(std::string const &gameName, StatisticsGameTable const &statisticsGameTable);

    void render() const override;


    };

} // ui_elements

#endif //ATHENA_TABLECONTAINER_H
