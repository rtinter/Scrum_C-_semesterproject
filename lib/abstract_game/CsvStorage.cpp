//
// Created by Admin on 06.06.2024.
//

#include <fstream>
#include <sstream>
#include "CsvStorage.hpp"
#include "GameRunThroughCsvWriter.hpp"


namespace abstract_game {
    const std::string SESSION_CSV_FILENAME {"game_session.csv"};
    const std::string RUNTHROUGH_CSV_FILENAME {"game_runthroughs.csv"};

    void CsvStorage::saveGameSession(size_t sessionUID, int userID, GameID gameID,
                                     long long startTime, long long endTime,
                                     unsigned long long duration, bool ended) {
        std::ofstream file(SESSION_CSV_FILENAME, std::ios::app); // Open file in append mode
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << SESSION_CSV_FILENAME << std::endl;
            return;
        }

        // Check if the file is empty before writing the header
        if (file.tellp() == 0) {
            file << "GameSessionUID,UserID,GameID,StartTime,EndTime,DurationInSeconds,Ended\n";
        }

        // Write session data
        std::stringstream ss;
        ss << sessionUID << ","
           << userID << ","
           << static_cast<int>(gameID) << ","
           << startTime << ","
           << endTime << ","
           << duration << ","
           << ended << "\n";
        std::string data {ss.str()};
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
        bool isEmpty {infile.tellg() == 0};
        infile.close();


        GameRunThroughCsvWriter writer(RUNTHROUGH_CSV_FILENAME);

        if (isEmpty) {
            writer.writeHeader({"GameRunThroughUID", "GameSessionUID", "Result", "ResultUnit"});
        }


        for (const auto &runThrough: _gameRunThroughs) {
            writer.writeRow<std::string>({std::to_string(runThrough.gameRunThroughUID),
                             std::to_string(runThrough.gameSessionUID),
                             std::to_string(runThrough.result),
                             runThrough.resultUnit});
        }
        writer.close();
    }

    void CsvStorage::getUserData(int userID) {
        // Implementation to read user data from the CSV file
    }

} // abstract_game