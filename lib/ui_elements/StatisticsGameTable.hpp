//
// Created by zarathustra on 30.05.24.
//

#ifndef STATISTIKGAMETABELLE_H
#define STATISTIKGAMETABELLE_H
#include <chrono>
#pragma once

#include <imgui.h>
#include <map>
#include<vector>
#include <string>
#include <UiElement.hpp>
#include <utility>
#include <vector>
#include <unordered_map>

namespace ui_elements {
    class StatisticsGameTable : public UiElement {
        std::map<int, //ID
            std::vector<std::string> // whatever is to be included in the table
        > _input;
        std::string _datum;
        std::string _dauer;
        std::string _werte;
        int _column_size;

    public:
        explicit StatisticsGameTable(std::map<int, //ordered item number
            std::vector<std::string> // whatever is to be included in the table, with the first row beeing the column
                                    //name and the following filling in
        > input);



        void render() const override; //renders the table

        void createTable() const; //creates the table

        void createTableHead() const;//create the columns name, to be found as the first (0) value of the map

        void createTableRows() const; //creates the Rows of the table
    };
}
#endif //STATISTIKGAMETABELLE_H
