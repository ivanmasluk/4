#pragma once

#include "Handler.h"

class MoveHandler : public Handler {
public:
    explicit MoveHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
