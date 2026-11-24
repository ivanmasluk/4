#pragma once

#include "Command.h"

class AttackCommand : public Command {
private:
    int attackerId_;
    int targetId_;

public:
    AttackCommand(std::shared_ptr<GameMediator> mediator,
                  int attackerId,
                  int targetId);
    bool execute() override;
};
