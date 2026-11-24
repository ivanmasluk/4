#pragma once

#include "LogEvent.h"

#include <string>

class ILogFormatter {
public:
    virtual ~ILogFormatter() = default;

    virtual std::string format(const LogEvent& event) = 0;
};
