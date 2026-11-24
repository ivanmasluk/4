#pragma once

#include "Handler.h"

class BuildHandler : public Handler {
public:
    explicit BuildHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
