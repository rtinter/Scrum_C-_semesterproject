#pragma once

#include <string>
#include <vector>

struct DiagramQuestion {
    std::string image;
    std::string question;
    std::string answer;
    std::string explanation;

    std::vector<std::string> answers;
};
