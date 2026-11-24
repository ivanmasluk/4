#pragma once

#include "Handler.h"

class StatsHandler : public Handler {
public:
    explicit StatsHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
