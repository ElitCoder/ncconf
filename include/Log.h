#pragma once

#include <iostream>
#include <mutex>
#include <sstream>

#define LOG_PRINT_STREAM    (std::cout)
#define LOG_FLUSH_STREAM    (std::flush)

enum {
	DEBUG,
	INFO,
	NONE,
	ERR,
	WARN,
};

class Log : public std::ostringstream {
public:
	Log() {
        level_ = NONE;
    }

	Log(int level) {
        level_ = level;
    }

	~Log() {
        std::lock_guard<std::mutex> guard(print_mutex_);

        switch (level_) {
            case DEBUG: LOG_PRINT_STREAM << "[DEBUG] ";
                break;
            case NONE:
                break;
            case INFO: LOG_PRINT_STREAM << "[INFO] ";
                break;
            case ERR: LOG_PRINT_STREAM << "[ERROR] ";
                break;
            case WARN: LOG_PRINT_STREAM << "[WARNING] ";
                break;
            default: LOG_PRINT_STREAM << "[UNKNOWN LEVEL] ";
        }

        LOG_PRINT_STREAM << str();

        if (level_ != NONE) {
            LOG_PRINT_STREAM << std::endl;
        }

        LOG_PRINT_STREAM << LOG_FLUSH_STREAM;
    }

private:
	static std::mutex print_mutex_;
	int level_;
};

std::mutex Log::print_mutex_;