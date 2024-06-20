#include <fstream>
#include <sstream>
#include "CsvStorage.hpp"
#include "GameRunThroughCsvWriter.hpp"
#include "Session.hpp"
#include "CsvParser.hpp"
#include <iostream>

namespace abstract_game {
    const std::string SESSION_CSV_FILENAME {"game_session.csv"};
    const std::string RUNTHROUGH_CSV_FILENAME {"game_runthroughs.csv"};

    std::string getDateString(time_t timestamp)
    {
        std::stringstream ss;
        ss << std::put_time(std::localtime(&timestamp), "%d.%m.%Y");
        return ss.str();
    }

    void CsvStorage::saveGameSession(
            size_t sessionUID,
            int userID,
            GameID gameID,
            long long startTime,
            long long endTime,
            time_t start,
            time_t end,
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

        std::cout << getDateString(end) << std::endl;
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
            std::ostringstream oss;
            oss.precision(2);
            oss << std::fixed << runThrough.result;

            std::string result = oss.str();
            writer.writeRow({std::to_string(runThrough.gameRunThroughUID),
                             std::to_string(runThrough.gameSessionUID),
                             oss.str(),
                             runThrough.resultUnit});
        }
        writer.close();
    }

    std::vector<Session> CsvStorage::getUserData(int userID) {
        csv::CsvParser parser(SESSION_CSV_FILENAME);
        std::vector<Session> sessions;
        // GameSessionUID,UserID,GameID,StartTime,EndTime,StartTimestamp,EndTimestamp,DurationInSeconds,Ended

        for(const auto &row : parser.parse()){
            const auto userId = std::atoi(row[3].c_str());

            if(userId != userID)
                continue;


            // GameID,GameSessionUID,UserID,StartTimestamp,EndTimestamp,DurationInSeconds,Ended
            const auto gameId { row[0] };
            const size_t gameSessionId {static_cast<size_t>(std::atoi(row[1].c_str()))};
            const auto startTimestamp { static_cast<time_t>(std::stoll(row[3])) };
            const auto endTimestamp { static_cast<time_t>(std::stoll(row[4])) };
            // const auto durationInSeconds { std::atoi(row[5].c_str()) };
            const auto ended { static_cast<bool>(row[6].c_str()) };

            auto diff = std::chrono::seconds(endTimestamp) - std::chrono::seconds(startTimestamp);
            std::string date = getDateString(endTimestamp);

            sessions.emplace_back(Session{
                    .gameSessionId = gameSessionId,
                    .start = startTimestamp,
                    .end = endTimestamp,
                    .date = date,
                    .duration = diff.count(),
                    .ended = ended
            });
        }
        // Implementation to read user data from the CSV file
        return sessions;
    }

} // abstract_game