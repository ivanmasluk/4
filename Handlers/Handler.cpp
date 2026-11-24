#include "Handler.h"

Handler::Handler(std::shared_ptr<GameFacade> facade)
    : facade_(std::move(facade)) {
}

void Handler::setNext(std::shared_ptr<Handler> next) {
    next_ = std::move(next);
}

bool Handler::passToNext(const std::string& cmd) {
    if (!next_) {
        return false;
    }
    return next_->handle(cmd);
}
