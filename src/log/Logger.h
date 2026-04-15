#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
    public:
    static void Log(LogLevel level, const std::string& message);
    static void Info(const std::string& msg) {Log(LogLevel::Info, msg);}
    static void Warn(const std::string& msg) {Log(LogLevel::Warning, msg);}
    static void Error(const std::string& msg) {Log(LogLevel::Error, msg);}
};