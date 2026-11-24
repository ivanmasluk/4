#include "AttackCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

AttackCommand::AttackCommand(std::shared_ptr<GameMediator> mediator,
                             int attackerId,
                             int targetId)
    : Command(std::move(mediator)),
      attackerId_(attackerId),
      targetId_(targetId) {
}

bool AttackCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Attack " << attackerId_
              << " -> " << targetId_ << "\n";
    return mediator_->resolveCombat(attackerId_, targetId_);
}
