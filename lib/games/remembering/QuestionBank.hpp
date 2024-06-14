#pragma once

#include <vector>
#include <string>
#include <memory>

struct QuestionBank {

    struct Question {
        std::string question;
        std::vector<std::string> answers;
        int correctAnswerIndex;
    };

    struct QuestionSet {
        std::string text;
        std::vector<Question> questions;
    };

    QuestionBank();

    const QuestionSet &getRandomQuestionSet() const;

private:
    std::vector<QuestionSet> _questionSets;
};

