#pragma once

#include "Command.h"

class CollectResourceCommand : public Command {
private:
    int unitId_;
    int resourcePointId_;

public:
    CollectResourceCommand(std::shared_ptr<GameMediator> mediator,
                           int unitId,
                           int resourcePointId);
    bool execute() override;
};
