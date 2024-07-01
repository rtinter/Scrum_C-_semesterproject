#pragma once

#include <Logger.hpp>
#include <fstream>
#include <vector>
#include "DiagramQuestion.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class DiagramHelper {
public:
    static std::vector<DiagramQuestion> getQuestions(){
        logger::Logger& logger {logger::Logger::getInstance()};
        std::vector<DiagramQuestion> questions;

        std::fstream file("./assets/games/diagrams/diagrams.json");
        if (!file) {
            logger.log("Unable to open file diagrams.json", logger::LogType::SEVERE);
            return questions;
        }

        json data = json::parse(file);
        for(auto const &token : data){
            std::vector<std::string> answers;
            for(auto const &answer : token["answers"]){
                std::string a;
                answer.get_to(a);
                answers.emplace_back(a);
            }

            questions.emplace_back(DiagramQuestion{
                .image = token["image"],
                .question = token["question"],
                .answer = token["answer"],
                .explanation = token["explanation"],
                .answers = answers
            });
        }

        file.close();

        return questions;
    }
};
