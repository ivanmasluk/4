#include "CollectResourceCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

CollectResourceCommand::CollectResourceCommand(std::shared_ptr<GameMediator> mediator,
                                               int unitId,
                                               int resourcePointId)
    : Command(std::move(mediator)),
      unitId_(unitId),
      resourcePointId_(resourcePointId) {
}

bool CollectResourceCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Collect unit=" << unitId_
              << " from=" << resourcePointId_ << "\n";
    return mediator_->collectResource(unitId_, resourcePointId_);
}
