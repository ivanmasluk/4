#pragma once

#include "Command.h"
#include <string>

class BuildBuildingCommand : public Command {
private:
    std::string buildingType_;
    int x_;
    int y_;

public:
    BuildBuildingCommand(std::shared_ptr<GameMediator> mediator,
                         const std::string& buildingType,
                         int x,
                         int y);
    bool execute() override;
};
