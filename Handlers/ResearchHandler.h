#pragma once

#include "Handler.h"

class ResearchHandler : public Handler {
public:
    explicit ResearchHandler(std::shared_ptr<GameFacade> facade);
    bool handle(const std::string& cmd) override;
};
