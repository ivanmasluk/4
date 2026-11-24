#include "DistributeResourcesCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

DistributeResourcesCommand::DistributeResourcesCommand(
        std::shared_ptr<GameMediator> mediator,
        const std::string& resourceType,
        const std::string& targetBuildingType,
        int amount)
    : Command(std::move(mediator)),
      resourceType_(resourceType),
      targetBuildingType_(targetBuildingType),
      amount_(amount) {
}

bool DistributeResourcesCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Distribute " << amount_ << " "
              << resourceType_ << " to " << targetBuildingType_ << "\n";
    return mediator_->distributeResources(resourceType_, targetBuildingType_, amount_);
}
