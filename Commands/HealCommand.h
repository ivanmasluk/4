#pragma once

#include "Command.h"

class HealCommand : public Command {
private:
    int unitId_;
    int buildingId_;

public:
    HealCommand(std::shared_ptr<GameMediator> mediator,
                int unitId,
                int buildingId);
    bool execute() override;
};
