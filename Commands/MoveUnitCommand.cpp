#include "MoveUnitCommand.h"
#include "../Mediator/GameMediator.h"
#include "../Systems/UnitManager.h"
#include "../Units/Unit.h"
#include <iostream>

MoveUnitCommand::MoveUnitCommand(std::shared_ptr<GameMediator> mediator,
                                 int unitId,
                                 int targetX,
                                 int targetY)
    : Command(std::move(mediator)),
      unitId_(unitId),
      targetX_(targetX),
      targetY_(targetY) {
}

bool MoveUnitCommand::execute() {
    if (!mediator_) {
        moved_ = false;
        return false;
    }

    Unit* unit = mediator_->getUnitManager()->getUnitById(unitId_);
    if (unit == nullptr) {
        std::cout << "[Command] MoveUnit: юнит не найден\n";
        moved_ = false;
        return false;
    }

    prevX_ = unit->getX();
    prevY_ = unit->getY();

    std::cout << "[Command] MoveUnit id=" << unitId_
              << " to (" << targetX_ << "," << targetY_ << ")\n";

    moved_ = mediator_->moveUnit(unitId_, targetX_, targetY_);
    return moved_;
}

void MoveUnitCommand::undo() {
    if (!moved_ || !mediator_) {
        return;
    }

    std::cout << "[Command] Undo MoveUnit id=" << unitId_
              << " back to (" << prevX_ << "," << prevY_ << ")\n";
    mediator_->moveUnit(unitId_, prevX_, prevY_);
    moved_ = false;
}

bool MoveUnitCommand::canUndo() const {
    return moved_;
}
