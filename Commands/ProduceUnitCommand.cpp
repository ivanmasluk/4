#include "ProduceUnitCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

ProduceUnitCommand::ProduceUnitCommand(std::shared_ptr<GameMediator> mediator,
                                       const std::string& unitType,
                                       int buildingId)
    : Command(std::move(mediator)),
      unitType_(unitType),
      buildingId_(buildingId) {
}

bool ProduceUnitCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Produce " << unitType_
              << " in building " << buildingId_ << "\n";
    return mediator_->produceUnit(unitType_, buildingId_);
}
