#include "CsvFormatter.h"

#include <sstream>

std::string CsvFormatter::sanitize(const std::string& value) {
    std::string result;
    result.reserve(value.size());

    for (char c : value) {
        if (c == ';' || c == '\n' || c == '\r') {
            result += ' ';
        } else {
            result += c;
        }
    }
    return result;
}

std::string CsvFormatter::format(const LogEvent& event) {
    std::ostringstream oss;
    oss << sanitize(event.timestamp) << ';'
        << sanitize(event.level)     << ';'
        << sanitize(event.source)    << ';'
        << sanitize(event.message);
    return oss.str();
}
