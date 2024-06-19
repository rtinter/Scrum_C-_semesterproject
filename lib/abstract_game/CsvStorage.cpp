//
// Created by Admin on 06.06.2024.
//

#include <fstream>
#include <sstream>
#include "CsvStorage.hpp"
#include "GameRunThroughCsvWriter.hpp"
#include "Session.hpp"


namespace abstract_game {
    const std::string SESSION_CSV_FILENAME {"game_session.csv"};
    const std::string RUNTHROUGH_CSV_FILENAME {"game_runthroughs.csv"};

    void CsvStorage::saveGameSession(
            size_t sessionUID,
            int userID,
            GameID gameID,
            long long startTime,
            long long endTime,
            time_t start,
            time_t end,
            unsigned long long duration,
            bool ended
        )
    {

        bool isEmpty = false;

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
            writer.writeRow({std::to_string(runThrough.gameRunThroughUID),
                             std::to_string(runThrough.gameSessionUID),
                             std::to_string(runThrough.result),
                             runThrough.resultUnit});
        }
        writer.close();
    }

    std::vector<Session> CsvStorage::getUserData(int userID) {
        std::vector<Session> sessions;
        // GameSessionUID,UserID,GameID,StartTime,EndTime,StartTimestamp,EndTimestamp,DurationInSeconds,Ended
        rapidcsv::Document document(SESSION_CSV_FILENAME);
        std::vector<size_t> gameSessionUID {document.GetColumn<size_t>("GameSessionUID")};
        std::vector<int> userId {document.GetColumn<int>("userId")};
        std::vector<int> gameId {document.GetColumn<int>("GameID")};
        std::vector<time_t> startTime {document.GetColumn<time_t>("StartTime")};
        std::vector<time_t> endTime {document.GetColumn<time_t>("EndTime")};
        std::vector<int64_t> duration {document.GetColumn<int64_t>("Duration")};

        size_t rowCount {document.GetRowCount()};
        for(size_t row{0}; row < rowCount; ++row){
            if(userId[row] != userID)
                continue;

            sessions.emplace_back(Session{
                .start = startTime[row],
                .end = startTime[row],
            });
        }
        // Implementation to read user data from the CSV file
        return sessions;
    }

} // abstract_game