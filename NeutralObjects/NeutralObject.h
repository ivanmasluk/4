#pragma once

#include <memory>
#include <ostream>
#include <string>

class Unit;
class ILogger;

class NeutralObject {
public:
    virtual ~NeutralObject() = default;
    virtual void interact(Unit& unit) = 0;
    virtual char getSymbol() const = 0;

    void setLogger(std::shared_ptr<ILogger> logger);
    std::shared_ptr<ILogger> getLogger() const;

protected:
    void logEnv(const std::string& message) const;

private:
    std::shared_ptr<ILogger> logger_;
};

std::ostream& operator<<(std::ostream& os, const NeutralObject& obj);
