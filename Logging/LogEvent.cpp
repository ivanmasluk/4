#include "LogEvent.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

LogEvent::LogEvent(std::string level_,
                   std::string source_,
                   std::string message_)
    : timestamp(now())
    , level(std::move(level_))
    , source(std::move(source_))
    , message(std::move(message_))
{
}

std::string LogEvent::now() {
    using clock = std::chrono::system_clock;
    const auto now = clock::now();
    const std::time_t t = clock::to_time_t(now);

    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
