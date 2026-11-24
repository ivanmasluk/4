#pragma once

#include "Command.h"

class MoveUnitCommand : public Command {
private:
    int unitId_;
    int targetX_;
    int targetY_;
    int prevX_ = 0;
    int prevY_ = 0;
    bool moved_ = false;

public:
    MoveUnitCommand(std::shared_ptr<GameMediator> mediator,
                    int unitId,
                    int targetX,
                    int targetY);
    bool execute() override;
    void undo() override;
    bool canUndo() const override;
};
