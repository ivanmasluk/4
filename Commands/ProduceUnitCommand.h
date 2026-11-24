#pragma once

#include "Command.h"
#include <string>

class ProduceUnitCommand : public Command {
private:
    std::string unitType_;
    int buildingId_;

public:
    ProduceUnitCommand(std::shared_ptr<GameMediator> mediator,
                       const std::string& unitType,
                       int buildingId);
    bool execute() override;
};
