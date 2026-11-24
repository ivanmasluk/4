#pragma once

#include "Handler.h"

class SetFormatHandler : public Handler {
public:
    explicit SetFormatHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
