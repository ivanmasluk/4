#pragma once

#include "Handler.h"

class CreateHandler : public Handler {
public:
    explicit CreateHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
