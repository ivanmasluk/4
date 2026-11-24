#include "JsonFormatter.h"

#include <cstdio>
#include <sstream>

std::string JsonFormatter::escape(const std::string& value) {
    std::string result;
    result.reserve(value.size() + 8);

    for (char c : value) {
        switch (c) {
            case '"':  result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\b': result += "\\b";  break;
            case '\f': result += "\\f";  break;
            case '\n': result += "\\n";  break;
            case '\r': result += "\\r";  break;
            case '\t': result += "\\t";  break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    char buf[8];
                    std::snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned char>(c));
                    result += buf;
                } else {
                    result += c;
                }
                break;
        }
    }
    return result;
}

std::string JsonFormatter::format(const LogEvent& event) {
    std::ostringstream oss;
    oss << '{'
        << "\"timestamp\":\"" << escape(event.timestamp) << "\","
        << "\"level\":\""     << escape(event.level)     << "\","
        << "\"source\":\""    << escape(event.source)    << "\","
        << "\"message\":\""   << escape(event.message)   << "\""
        << '}';
    return oss.str();
}
