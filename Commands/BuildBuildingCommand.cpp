#include "BuildBuildingCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

BuildBuildingCommand::BuildBuildingCommand(std::shared_ptr<GameMediator> mediator,
                                           const std::string& buildingType,
                                           int x,
                                           int y)
    : Command(std::move(mediator)),
      buildingType_(buildingType),
      x_(x),
      y_(y) {
}

bool BuildBuildingCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Build " << buildingType_
              << " at (" << x_ << "," << y_ << ")\n";
    return mediator_->buildBuilding(buildingType_, x_, y_);
}
