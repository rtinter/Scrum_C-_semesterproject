#include "CsvStorage.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "CsvParser.hpp"
#include "GameRunThroughCsvWriter.hpp"

namespace abstract_game {
    std::string const SESSION_CSV_FILENAME{"game_session.csv"};
    std::string const RUNTHROUGH_CSV_FILENAME{"game_runthroughs.csv"};

    std::string CsvStorage::getDateString(time_t const timestamp) {
        std::stringstream ss;
        ss << std::put_time(std::localtime(&timestamp), "%d.%m.%Y");
        return ss.str();
    }

    void CsvStorage::saveGameSession(
        size_t sessionUID,
        int userID,
        GameID gameID,
        time_t start,
        time_t end,
        bool ended) {
        bool isEmpty{false};

        // Check if the file is empty before opening in append mode
        std::ifstream infile(SESSION_CSV_FILENAME);
        if (infile.peek() == std::ifstream::traits_type::eof()) {
            isEmpty = true;
        }
        infile.close();

        std::ofstream file(SESSION_CSV_FILENAME, std::ios::app); // Open file in append mode
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << SESSION_CSV_FILENAME << std::endl;
            return;
        }

        // Write the header if the file was empty
        if (isEmpty) {
            file << "GameID,GameSessionUID,UserID,StartTimestamp,EndTimestamp,Ended\n";
        }

        // GameID,GameSessionUID,UserID,DurationInSeconds, StartTimestamp,EndTimestamp,Ended
        // 1001,10071369308003187873,1,4,1718880176,1718880180,1
        // Write session data
        std::stringstream ss;
        ss
                << static_cast<int>(gameID) << ","
                << sessionUID << ","
                << userID << ","
                << start << ","
                << end << ","
                << ended << "\n";

        std::string const data{ss.str()};
        file << data;
        file.close();
    }

    void CsvStorage::saveRunThroughs(std::vector<GameRunThrough> _gameRunThroughs) {
        std::ofstream file(RUNTHROUGH_CSV_FILENAME, std::ios::app); // Open file in append mode
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << RUNTHROUGH_CSV_FILENAME << std::endl;
            return;
        }
        file.close();

        // Check if the file is empty before writing the header
        std::ifstream infile(RUNTHROUGH_CSV_FILENAME);
        infile.seekg(0, std::ios::end);
        bool const isEmpty{infile.tellg() == 0};
        infile.close();


        GameRunThroughCsvWriter writer(RUNTHROUGH_CSV_FILENAME);

        if (isEmpty) {
            writer.writeHeader({"GameRunThroughUID", "GameSessionUID", "Result", "ResultUnit"});
        }


        for (auto const &runThrough: _gameRunThroughs) {
            std::ostringstream oss;
            oss.precision(2);
            oss << std::fixed << runThrough.result;

            std::string result{oss.str()};
            writer.writeRow({
                std::to_string(runThrough.gameRunThroughUID),
                std::to_string(runThrough.gameSessionUID),
                oss.str(),
                runThrough.resultUnit
            });
        }
        writer.close();
    }
} // abstract_game
