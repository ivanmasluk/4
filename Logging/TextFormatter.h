#pragma once

#include "ILogFormatter.h"

class TextFormatter : public ILogFormatter {
public:
    std::string format(const LogEvent& event) override;
};
