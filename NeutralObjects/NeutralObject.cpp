#include "NeutralObject.h"
#include "../Logging/ILogger.h"
#include "../Logging/LogEvent.h"

void NeutralObject::setLogger(std::shared_ptr<ILogger> logger) {
    logger_ = std::move(logger);
}

std::shared_ptr<ILogger> NeutralObject::getLogger() const {
    return logger_;
}

void NeutralObject::logEnv(const std::string& message) const {
    if (logger_ == nullptr) {
        return;
    }
    logger_->log(LogEvent("INFO", "ENV", message));
}

std::ostream& operator<<(std::ostream& os, const NeutralObject& obj) {
    os << "NeutralObject('" << obj.getSymbol() << "')";
    return os;
}
