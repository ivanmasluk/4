#include "Command.h"

Command::Command(std::shared_ptr<GameMediator> mediator)
    : mediator_(std::move(mediator)) {
}

void Command::undo() {
}

bool Command::canUndo() const {
    return false;
}
