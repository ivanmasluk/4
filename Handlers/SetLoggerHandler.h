#pragma once

#include "Handler.h"

class SetLoggerHandler : public Handler {
public:
    explicit SetLoggerHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
