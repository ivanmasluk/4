#pragma once

#include "ILogger.h"

#include <memory>

class ConsoleLogger : public ILogger {
public:
    explicit ConsoleLogger(std::shared_ptr<ILogFormatter> formatter = nullptr);

    void log(const LogEvent& event) override;
    void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;

private:
    std::shared_ptr<ILogFormatter> formatter_;
};
