#include "Logger.h"

void Logger::Log(LogLevel level, const std::string& message) {
    std::string levelStr;
        switch (level) {
            case LogLevel::Info:    levelStr = "[INFO]"; break;
            case LogLevel::Warning: levelStr = "[WARNING]"; break;
            case LogLevel::Error:   levelStr = "[ERROR]"; break;
        }

        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << std::put_time(std::localtime(&now), "%H:%M:%S ") 
                  << levelStr << ": " << message << std::endl;
}