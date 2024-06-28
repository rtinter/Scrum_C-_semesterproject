#pragma once

#include <vector>
#include <string>
#include <memory>

/**
 * @brief Manages a collection of question sets, each containing multiple choice questions.
 */
struct QuestionBank {

    /**
     * @brief Represents a single multiple choice question.
     */
    struct Question {
        std::string question;
        std::vector<std::string> answers;
        int correctAnswerIndex;
    };

    /**
     * @brief struct that stores every question.
     */
    struct QuestionSet {
        std::string text;
        std::vector<Question> questions;
    };

    /**
     * @brief Constructor that initializes the questionbank.
     */
    QuestionBank();

    /**
    * @brief Retrieves a random question set from the bank.
    * @return const QuestionSet& A reference to the randomly selected question set.
    */
    QuestionSet const &getRandomQuestionSet() const;

private:
    /**
    * @brief storage of all questionsets available in the bank.
    */
    std::vector<QuestionSet> _questionSets;
};

