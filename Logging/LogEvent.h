#pragma once

#include <string>

struct LogEvent {
    std::string timestamp;
    std::string level;
    std::string source;
    std::string message;

    LogEvent() = default;

    LogEvent(std::string level_,
             std::string source_,
             std::string message_);

    static std::string now();
};
