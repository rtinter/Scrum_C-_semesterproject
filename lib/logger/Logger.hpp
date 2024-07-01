#pragma once

#include <chrono>
#include <fstream>
#include <future>
#include <iomanip>
#include <queue>
#include <sstream>
#include <string>
#include <thread>

#include "QueueEntry.hpp"
#include "LogType.hpp"

namespace logger {
    /**
     * @brief The Logger class is responsible for logging messages to a file.
     *
     * The Logger class provides methods for logging messages of different types (DEBUG, INFORMATION, SEVERE).
     * It also provides methods for flushing the log queue and stopping the logging process.
     */
    class Logger final {
    private:
        std::queue<QueueEntry> _sink;

        bool _initialized{false};
        bool _stop{false};
        std::ofstream _outputStream;

        LogType _type{LogType::DEBUG};
        std::future<void> _sinkBackgroundTask{};

        void log(QueueEntry const &entry);

    public:
        static Logger &getInstance();

        virtual ~Logger();

        void flush();

        void log(std::string const &content, LogType type);

        static void sinkTask(Logger &logger);

        static std::string getDateString(time_t timestamp) {
            std::stringstream ss;
            ss << std::put_time(std::localtime(&timestamp), "%d.%m.%Y - %H:%M:%S");
            return ss.str();
        }

        Logger &operator<<(std::string const &content) {
            this->_sink.emplace(QueueEntry{
                .timestamp = time(nullptr),
                .content = content,
                .entryType = _type,
            });
            return *this;
        }

        Logger &operator<<(int content) {
            this->_sink.emplace(QueueEntry{
                .timestamp = time(nullptr),
                .content = std::to_string(content),
                .entryType = _type,
            });
            return *this;
        }

        Logger &operator<<(float content) {
            this->_sink.emplace(QueueEntry{
                .timestamp = time(nullptr),
                .content = std::to_string(content),
                .entryType = _type,
            });
            return *this;
        }

        Logger &operator<<(LogType const type) {
            this->_type = type;
            return *this;
        }
    };

    void createLogDir(std::string const &path);
}
