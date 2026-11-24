#pragma once

#include "../Commands/Command.h"
#include "../Commands/CommandHistory.h"
#include "../Handlers/Handler.h"
#include "../Logging/ILogger.h"
#include "../Logging/LoggingProxy.h"
#include <memory>
#include <string>

class GameMediator;

class GameFacade {
private:
    std::shared_ptr<GameMediator> mediator_;
    std::shared_ptr<Handler> chainRoot_;
    CommandHistory history_;
    std::shared_ptr<LoggingProxy> logger_;

public:
    explicit GameFacade(std::shared_ptr<GameMediator> mediator);

    void setHandlerChain(std::shared_ptr<Handler> root);
    void setLogger(std::shared_ptr<LoggingProxy> logger);
    std::shared_ptr<LoggingProxy> getLogger() const;

    bool setLoggerType(const std::string& type, const std::string& filename = "game_log.txt");
    bool setFormatType(const std::string& type);

    void logUser(const std::string& message);
    void log(const std::string& level,
             const std::string& source,
             const std::string& message);

    bool createUnit(const std::string& type, int x, int y);
    bool moveUnit(int unitId, int x, int y);
    bool attack(int attackerId, int targetId);
    bool collectResource(int unitId, int resourcePointId);
    bool heal(int unitId, int buildingId);
    bool buildBuilding(const std::string& buildingType, int x, int y);
    bool research(const std::string& technologyId);
    bool distributeResources(const std::string& resourceType,
                             const std::string& buildingType,
                             int amount);
    bool produceUnit(const std::string& unitType, int buildingId);
    void getStats(const std::string& mode = "all");

    bool executeCommand(std::shared_ptr<Command> command);
    bool undoLastCommand();
    bool processInput(const std::string& input);

    std::shared_ptr<GameMediator> getMediator() const;
};
