#pragma once

#include "ILogger.h"
#include "ILogFormatter.h"

#include <memory>
#include <string>

class LoggingProxy : public ILogger {
public:
    LoggingProxy();

    void log(const LogEvent& event) override;
    void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;

    void setLogger(std::unique_ptr<ILogger> logger);

    bool setLoggerFromString(const std::string& type,
                             const std::string& filename = "game_log.txt");

    bool setFormatterFromString(const std::string& type);

    ILogger* currentLogger() const;
    std::shared_ptr<ILogFormatter> currentFormatter() const;

private:
    std::unique_ptr<ILogger> currentLogger_;
    std::shared_ptr<ILogFormatter> formatter_;
};
