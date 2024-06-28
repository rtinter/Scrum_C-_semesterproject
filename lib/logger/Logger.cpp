#include "Logger.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace logger {
    void Logger::flush() {
    }

    void Logger::log(const QueueEntry& entry) {
        if(entry.entryType == QueueEntryType::DEBUG){
            _outputStream << "[DEBUG]: " << getDateString(entry.timestamp) << " " << entry.content << std::endl;
        }
        if(entry.entryType == QueueEntryType::INFORMATION){
            _outputStream << "[INFORMATION]: " << getDateString(entry.timestamp) << " " << entry.content << std::endl;
        }
        if(entry.entryType == QueueEntryType::SEVERE){
            _outputStream << "[SEVERE]: " << getDateString(entry.timestamp)  << " " << entry.content << std::endl;
        }
    }

    void Logger::sinkTask(Logger &logger){
        while(!logger._stop){
            while(!logger._sink.empty()){
                logger.log(logger._sink.front());
                logger._sink.pop();
            }
        }
    }

    logger::Logger& logger::Logger::getInstance() {
        static Logger logger;
        if (!logger._initialized) {
            std::string path {"session_"};
            path.append(std::to_string(time(nullptr)));
            path.append(".txt");
            logger._initialized = true;
            logger._outputStream.open(path);
            logger._sinkBackgroundTask = std::async(std::launch::async, [&](){
                sinkTask(logger);
            });
        }

        return logger;
    }

    Logger::~Logger() {
        this->_stop = true;
        this->flush();
        this->_outputStream.close();
    }
}