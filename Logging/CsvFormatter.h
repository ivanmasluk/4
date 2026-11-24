#pragma once

#include "ILogFormatter.h"

class CsvFormatter : public ILogFormatter {
public:
    std::string format(const LogEvent& event) override;

private:
    static std::string sanitize(const std::string& value);
};
