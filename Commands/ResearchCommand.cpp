#include "ResearchCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

ResearchCommand::ResearchCommand(std::shared_ptr<GameMediator> mediator,
                                 const std::string& technologyId)
    : Command(std::move(mediator)),
      technologyId_(technologyId) {
}

bool ResearchCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Research " << technologyId_ << "\n";
    return mediator_->startResearch(technologyId_);
}
