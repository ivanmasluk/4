#pragma once

#include <memory>
#include <string>

class GameFacade;

class Handler {
protected:
    std::shared_ptr<Handler> next_;
    std::shared_ptr<GameFacade> facade_;

public:
    explicit Handler(std::shared_ptr<GameFacade> facade);
    virtual ~Handler() = default;

    void setNext(std::shared_ptr<Handler> next);
    virtual bool handle(const std::string& cmd) = 0;

protected:
    bool passToNext(const std::string& cmd);
};
