#include "NullLogger.h"

void NullLogger::log(const LogEvent&) {
}

void NullLogger::setFormatter(std::shared_ptr<ILogFormatter>) {
}
