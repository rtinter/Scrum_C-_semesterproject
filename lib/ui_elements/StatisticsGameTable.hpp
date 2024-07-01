#pragma once

#include <map>
#include <string>
#include <vector>

#include "UiElement.hpp"

namespace ui_elements {
    class StatisticsGameTable final : public UiElement {
        std::map<int, //ID
            std::vector<std::string> // whatever is to be included in the table, the first (key= 0) value are the column
            //names
        > _input;
        int _column_size; //how many columns are there

    public:
        explicit StatisticsGameTable(std::map<int, //ordered item number
            std::vector<std::string> // whatever is to be included in the table, with the first row beeing the column
            //name and the following filling in
        > const &input);


        void render() override; //renders the table

        static void defaultTable(); //if there is no input creates this table

        void createTable() const; //creates the table according to the number of columns

        void createTableHead() const; //create the columns name, to be found as the first (0) value of the map

        void createTableRows() const; //creates the Rows of the table
    };
} // ui_elements
