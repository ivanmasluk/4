#include "LoggingProxy.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "NullLogger.h"
#include "FormatterFactory.h"
#include "TextFormatter.h"

#include <iostream>

LoggingProxy::LoggingProxy()
    : currentLogger_(std::make_unique<ConsoleLogger>())
    , formatter_(std::make_shared<TextFormatter>())
{
    if (currentLogger_) {
        currentLogger_->setFormatter(formatter_);
    }
}

void LoggingProxy::log(const LogEvent& event) {
    if (currentLogger_) {
        currentLogger_->log(event);
    }
}

void LoggingProxy::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
    formatter_ = std::move(formatter);
    if (currentLogger_ && formatter_) {
        currentLogger_->setFormatter(formatter_);
    }
}

void LoggingProxy::setLogger(std::unique_ptr<ILogger> logger) {
    currentLogger_ = std::move(logger);
    if (currentLogger_ && formatter_) {
        currentLogger_->setFormatter(formatter_);
    }
}

bool LoggingProxy::setLoggerFromString(const std::string& type,
                                       const std::string& filename) {
    if (type == "console") {
        setLogger(std::make_unique<ConsoleLogger>(formatter_));
        return true;
    }
    if (type == "file") {
        auto fileLogger = std::make_unique<FileLogger>(filename, formatter_);
        if (!fileLogger->isOpen()) {
            std::cerr << "[LoggingProxy] Не удалось переключить на файловый логгер, файл не открыт\n";
            return false;
        }
        setLogger(std::move(fileLogger));
        return true;
    }
    if (type == "null") {
        setLogger(std::make_unique<NullLogger>());
        return true;
    }

    std::cerr << "[LoggingProxy] Неизвестный тип логгера: " << type << '\n';
    return false;
}

bool LoggingProxy::setFormatterFromString(const std::string& type) {
    auto fmt = createFormatter(type);
    if (!fmt) {
        std::cerr << "[LoggingProxy] Неизвестный тип форматтера: " << type << '\n';
        return false;
    }
    setFormatter(std::move(fmt));
    return true;
}

ILogger* LoggingProxy::currentLogger() const {
    return currentLogger_.get();
}

std::shared_ptr<ILogFormatter> LoggingProxy::currentFormatter() const {
    return formatter_;
}
