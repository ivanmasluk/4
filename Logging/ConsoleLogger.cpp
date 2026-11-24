#include "ConsoleLogger.h"
#include "TextFormatter.h"

#include <iostream>

ConsoleLogger::ConsoleLogger(std::shared_ptr<ILogFormatter> formatter) {
    if (formatter) {
        formatter_ = std::move(formatter);
    } else {
        formatter_ = std::make_shared<TextFormatter>();
    }
}

void ConsoleLogger::log(const LogEvent& event) {
    if (!formatter_) {
        return;
    }
    std::cout << formatter_->format(event) << std::endl;
}

void ConsoleLogger::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
    formatter_ = std::move(formatter);
}
