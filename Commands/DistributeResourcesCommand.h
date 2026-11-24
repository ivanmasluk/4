#pragma once

#include "Command.h"
#include <string>

class DistributeResourcesCommand : public Command {
private:
    std::string resourceType_;
    std::string targetBuildingType_;
    int amount_;

public:
    DistributeResourcesCommand(std::shared_ptr<GameMediator> mediator,
                               const std::string& resourceType,
                               const std::string& targetBuildingType,
                               int amount);
    bool execute() override;
};
