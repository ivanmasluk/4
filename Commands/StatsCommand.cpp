#include "StatsCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

StatsCommand::StatsCommand(std::shared_ptr<GameMediator> mediator,
                           const std::string& mode)
    : Command(std::move(mediator)),
      mode_(mode) {
}

bool StatsCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] Stats mode=" << mode_ << "\n";
    mediator_->getStats(mode_);
    return true;
}
