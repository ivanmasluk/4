#pragma once

#include "Command.h"
#include <memory>
#include <vector>

class CommandHistory {
private:
    std::vector<std::shared_ptr<Command>> history_;

public:
    void push(std::shared_ptr<Command> command);
    bool undoLast();
    std::shared_ptr<Command> getLastCommand() const;
    bool empty() const;
    void clear();
};
