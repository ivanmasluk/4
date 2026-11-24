#pragma once

#include "Handler.h"

class HealHandler : public Handler {
public:
    explicit HealHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
