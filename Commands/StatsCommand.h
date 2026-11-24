#pragma once

#include "Command.h"
#include <string>

class StatsCommand : public Command {
private:
    std::string mode_;

public:
    explicit StatsCommand(std::shared_ptr<GameMediator> mediator,
                          const std::string& mode = "all");
    bool execute() override;
};
