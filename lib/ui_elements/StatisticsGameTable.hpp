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
    class StatisticsGameTable : public  UiElement {
         std::unordered_map<std::string, //UUID
            std::vector<std::string> // whatever is to be included in the table
            >_input;
        std::string _datum;
        std::string _dauer;
        std::string _werte;


    public:

        explicit StatisticsGameTable (std::unordered_map<std::string, //UUID
            std::vector<std::string> // whatever is to be included in the table
            > input);

        StatisticsGameTable (std::string datum, std::string dauer, std::string werte );
        void render() const override;
        void createTable() const;

    };
}
#endif //STATISTIKGAMETABELLE_H
