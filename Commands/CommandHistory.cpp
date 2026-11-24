#include "CommandHistory.h"

void CommandHistory::push(std::shared_ptr<Command> command) {
    if (command) {
        history_.push_back(std::move(command));
    }
}

bool CommandHistory::undoLast() {
    if (history_.empty()) {
        return false;
    }

    std::shared_ptr<Command> last = history_.back();
    if (!last->canUndo()) {
        return false;
    }

    last->undo();
    history_.pop_back();
    return true;
}

std::shared_ptr<Command> CommandHistory::getLastCommand() const {
    if (history_.empty()) {
        return nullptr;
    }
    return history_.back();
}

bool CommandHistory::empty() const {
    return history_.empty();
}

void CommandHistory::clear() {
    history_.clear();
}
