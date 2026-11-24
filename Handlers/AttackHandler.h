#pragma once

#include "Handler.h"

class AttackHandler : public Handler {
public:
    explicit AttackHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
