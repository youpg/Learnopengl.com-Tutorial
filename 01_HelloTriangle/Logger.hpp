#pragma once

#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    FATAL
};

class LogStream {
public:
    LogStream(LogLevel level) : level(level) {
        setColor(level);
        ss << "[" << levelToString(level) << "] ";
    }
    
    ~LogStream() {
        std::cout << ss.str() << std::endl;
        resetColor();
    }
    
    template<typename T>
    LogStream& operator<<(const T& msg) {
        ss << msg;
        return *this;
    }
    
    LogStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        manip(ss);
        return *this;
    }

private:
    static HANDLE getConsoleHandle() {
        static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        return hConsole;
    }

    static WORD getDefaultColor() {
        return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // White
    }

    static void setColor(LogLevel level) {
        WORD color;
        switch (level) {
            case LogLevel::DEBUG:
                color = FOREGROUND_BLUE | FOREGROUND_GREEN; // Cyan
                break;
            case LogLevel::INFO:
                color = FOREGROUND_GREEN; // Green
                break;
            case LogLevel::WARNING:
                color = FOREGROUND_RED | FOREGROUND_GREEN; // Yellow
                break;
            case LogLevel::FATAL:
                color = FOREGROUND_RED; // Red
                break;
            default:
                color = getDefaultColor();
        }
        SetConsoleTextAttribute(getConsoleHandle(), color);
    }
    
    static void resetColor() {
        SetConsoleTextAttribute(getConsoleHandle(), getDefaultColor());
    }

    static const char* levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::FATAL: return "FATAL";
            default: return "UNKNOWN";
        }
    }

    LogLevel level;
    std::stringstream ss;
};

#define LOG_DEBUG LogStream(LogLevel::DEBUG)
#define LOG_INFO LogStream(LogLevel::INFO)
#define LOG_WARNING LogStream(LogLevel::WARNING)
#define LOG_FATAL LogStream(LogLevel::FATAL)