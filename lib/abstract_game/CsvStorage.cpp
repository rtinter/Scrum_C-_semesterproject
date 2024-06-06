//
// Created by Admin on 06.06.2024.
//

#include <fstream>
#include <sstream>
#include "CsvStorage.hpp"


namespace abstract_game {
    const std::string CSV_FILENAME = "game_session.csv";

    void CsvStorage::saveGameSession(size_t sessionUID, int userID, int gameID,
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
            file << "GameID,UserID,GameSessionUID,StartTime,EndTime,DurationInSeconds,Ended\n";
        }
        // Write session data
        std::stringstream ss;
        ss << sessionUID << ","
           << userID << ","
           << gameID << ","
           << startTime << ","
           << endTime << ","
           << duration << ","
           << ended << "\n";
        std::string data {ss.str()};
        file << data;
        std::cout << data << std::endl;
        file.close();
    }

    void CsvStorage::getUserData(int userID) {
        // Implementation to read user data from the CSV file
    }

} // abstract_game