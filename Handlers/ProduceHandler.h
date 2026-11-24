#pragma once

#include "Handler.h"

class ProduceHandler : public Handler {
public:
    explicit ProduceHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
