#include "Logger.hpp"
#include <iostream>
#include <filesystem>

namespace logger {
    /*
     * Flushes the sink
     */
    void Logger::flush() {
        std::queue<QueueEntry> empty;
        // https://stackoverflow.com/questions/709146/how-do-i-clear-the-stdqueue-efficiently
        this->_sink.swap(empty);
    }

    /*
     * Writes content to file
     * @param entry a QueueEntry
     */
    void Logger::log(QueueEntry const &entry) {
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

    /*
     * Background Task for writing to IO
     * @param logger an Instance of Logger
     */
    void Logger::sinkTask(Logger &logger){
        while(!logger._stop){
            while(!logger._sink.empty()){
                logger.log(logger._sink.front());
                logger._sink.pop();
            }
        }
    }

    /*
     * Static Method for a singleton of Logger
     */
    logger::Logger& logger::Logger::getInstance() {
        static Logger logger;
        if (!logger._initialized) {
            std::string path {"logs/session_"};
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

    /*
     * Destructor of Logger,
     * additionally flushes sink, stops the background task and flushes left over entries.
     */
    Logger::~Logger() {
        this->_stop = true;
        this->flush();
        this->_outputStream.close();
    }

    /*
     * Manual Method for Logging
     * @param content a string
     * @param type a QueueEntryType
     */
    void Logger::log(std::string const &content, QueueEntryType type) {
        QueueEntry entry {
            .timestamp = time(nullptr),
            .content = content,
            .entryType = type
        };

        this->_sink.emplace(entry);
    }

    void createLogDir(const std::string &path) {
        if (!std::filesystem::exists(path)) {
            if (std::filesystem::create_directories(path)) {
                Logger::getInstance().log("Directory created: " + path, QueueEntryType::INFORMATION);
            } else {
                Logger::getInstance().log("Failed to create directory: " + path, QueueEntryType::SEVERE);
            }
        } else {
            Logger::getInstance().log("Failed to create directory: " + path, QueueEntryType::SEVERE);
        }
    }
}

