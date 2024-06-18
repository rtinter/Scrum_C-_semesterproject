//
// Created by Admin on 06.06.2024.
//

#include <fstream>
#include <sstream>
#include "CsvStorage.hpp"


namespace abstract_game {
    const std::string CSV_FILENAME = "game_session.csv";

    void CsvStorage::saveGameSession(size_t sessionUID, int userID, GameID gameID,
                                     long long startTime, long long endTime,
                                     unsigned long long duration, bool ended) {
        std::ofstream file(CSV_FILENAME, std::ios::app); // Open file in append mode
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << CSV_FILENAME << std::endl;
            return;
        }

        // Check if the file is empty before writing the header
        std::ifstream infile(CSV_FILENAME);
        infile.seekg(0, std::ios::end);
        bool isEmpty = infile.tellg() == 0;
        infile.close();

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

    std::vector<Session> CsvStorage::getUserData(int userID) {
        std::vector<Session> sessions;
        rapidcsv::Document doc(CSV_FILENAME);

        // file << "GameSessionUID,UserID,GameID,StartTime,EndTime,DurationInSeconds,Ended\n";
        std::vector<long> gameId = doc.GetColumn<long>("GameID");
        std::vector<size_t> gameSessionId = doc.GetColumn<size_t>("GameSessionUID");
        std::vector<int> userId = doc.GetColumn<int>("UserID");
        // std::vector<long> startTime = doc.GetColumn<long>("StartTime");
        // std::vector<long> endTime = doc.GetColumn<long>("EndTime");
        // std::vector<unsigned long long> duration = doc.GetColumn<unsigned long long>("DurationInSeconds");
        // std::vector<bool> ended = doc.GetColumn<bool>("Ended");

        int count = doc.GetRowCount();

        for(int row{0}; row < count; ++row){
            if(userId[row] != userID){
                continue;
            }
            Session session = {
                    .gameId = static_cast<GameID>(gameId[row]),
                    .userId = userId[row],
                    .gameSessionId = gameSessionId[row],
            };
            sessions.emplace_back(session);
        }

        return sessions;
        // Implementation to read user data from the CSV file
    }

} // abstract_game