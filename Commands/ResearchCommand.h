#pragma once

#include "Command.h"
#include <string>

class ResearchCommand : public Command {
private:
    std::string technologyId_;

public:
    ResearchCommand(std::shared_ptr<GameMediator> mediator,
                    const std::string& technologyId);
    bool execute() override;
};
