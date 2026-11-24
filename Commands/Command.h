#pragma once

#include <memory>

class GameMediator;

class Command {
protected:
    std::shared_ptr<GameMediator> mediator_;

public:
    explicit Command(std::shared_ptr<GameMediator> mediator);
    virtual ~Command() = default;

    virtual bool execute() = 0;
    virtual void undo();
    virtual bool canUndo() const;
};
