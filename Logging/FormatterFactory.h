#pragma once

#include "ILogFormatter.h"

#include <memory>
#include <string>

std::shared_ptr<ILogFormatter> createFormatter(const std::string& type);
