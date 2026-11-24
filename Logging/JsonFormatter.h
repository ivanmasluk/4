#pragma once

#include "ILogFormatter.h"

class JsonFormatter : public ILogFormatter {
public:
    std::string format(const LogEvent& event) override;

private:
    static std::string escape(const std::string& value);
};
