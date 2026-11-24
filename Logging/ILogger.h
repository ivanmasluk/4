#pragma once

#include "LogEvent.h"
#include "ILogFormatter.h"

#include <memory>

class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void log(const LogEvent& event) = 0;

    virtual void setFormatter(std::shared_ptr<ILogFormatter> formatter) = 0;
};
