#include "CreateUnitCommand.h"
#include "../Mediator/GameMediator.h"
#include <iostream>

CreateUnitCommand::CreateUnitCommand(std::shared_ptr<GameMediator> mediator,
                                     const std::string& type,
                                     int x,
                                     int y)
    : Command(std::move(mediator)),
      type_(type),
      x_(x),
      y_(y) {
}

bool CreateUnitCommand::execute() {
    if (!mediator_) {
        return false;
    }
    std::cout << "[Command] CreateUnit " << type_
              << " at (" << x_ << "," << y_ << ")\n";
    return mediator_->createUnit(type_, x_, y_);
}
