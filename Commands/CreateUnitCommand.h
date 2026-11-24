#pragma once

#include "Command.h"
#include <string>

class CreateUnitCommand : public Command {
private:
    std::string type_;
    int x_;
    int y_;

public:
    CreateUnitCommand(std::shared_ptr<GameMediator> mediator,
                      const std::string& type,
                      int x,
                      int y);
    bool execute() override;
};
