#include "HealCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

HealCommand::HealCommand(std::shared_ptr<GameMediator> mediator,
                         int unitId,
                         int buildingId)
    : Command(std::move(mediator)),
      unitId_(unitId),
      buildingId_(buildingId) {
}

bool HealCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Heal unit=" << unitId_
              << " at building=" << buildingId_ << "\n";
    return mediator_->healUnit(unitId_, buildingId_);
}
