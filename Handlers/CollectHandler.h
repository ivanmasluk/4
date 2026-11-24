#pragma once

#include "Handler.h"

class CollectHandler : public Handler {
public:
    explicit CollectHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
