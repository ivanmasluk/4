#include "GameFacade.h"
#include "../Mediator/GameMediator.h"
#include "../Commands/CreateUnitCommand.h"
#include "../Commands/MoveUnitCommand.h"
#include "../Commands/AttackCommand.h"
#include "../Commands/CollectResourceCommand.h"
#include "../Commands/HealCommand.h"
#include "../Commands/BuildBuildingCommand.h"
#include "../Commands/ResearchCommand.h"
#include "../Commands/DistributeResourcesCommand.h"
#include "../Commands/ProduceUnitCommand.h"
#include "../Commands/StatsCommand.h"
#include "../Logging/LogEvent.h"
#include <iostream>

GameFacade::GameFacade(std::shared_ptr<GameMediator> mediator)
    : mediator_(std::move(mediator))
    , logger_(std::make_shared<LoggingProxy>())
{
}

void GameFacade::setHandlerChain(std::shared_ptr<Handler> root) {
    chainRoot_ = std::move(root);
}

void GameFacade::setLogger(std::shared_ptr<LoggingProxy> logger) {
    logger_ = std::move(logger);
}

std::shared_ptr<LoggingProxy> GameFacade::getLogger() const {
    return logger_;
}

bool GameFacade::setLoggerType(const std::string& type, const std::string& filename) {
    if (!logger_) {
        return false;
    }
    const bool ok = logger_->setLoggerFromString(type, filename);
    if (ok) {
        logUser("set_logger " + type + (type == "file" ? (" " + filename) : ""));
    }
    return ok;
}

bool GameFacade::setFormatType(const std::string& type) {
    if (!logger_) {
        return false;
    }
    const bool ok = logger_->setFormatterFromString(type);
    if (ok) {
        logUser("set_format " + type);
    }
    return ok;
}

void GameFacade::logUser(const std::string& message) {
    log("INFO", "USER", message);
}

void GameFacade::log(const std::string& level,
                     const std::string& source,
                     const std::string& message) {
    if (logger_) {
        logger_->log(LogEvent(level, source, message));
    }
}

std::shared_ptr<GameMediator> GameFacade::getMediator() const {
    return mediator_;
}

bool GameFacade::executeCommand(std::shared_ptr<Command> command) {
    if (!command) {
        return false;
    }

    const bool ok = command->execute();
    if (ok) {
        history_.push(std::move(command));
    }
    return ok;
}

bool GameFacade::undoLastCommand() {
    if (!history_.undoLast()) {
        std::cout << "[Facade] Нечего отменять\n";
        return false;
    }
    std::cout << "[Facade] Последняя команда отменена\n";
    logUser("undo");
    return true;
}

bool GameFacade::processInput(const std::string& input) {
    if (input.empty()) {
        return false;
    }

    if (input == "undo") {
        return undoLastCommand();
    }

    if (!chainRoot_) {
        std::cout << "[Facade] Цепочка обработчиков не задана\n";
        return false;
    }

    // Log every user command before handling
    logUser(input);

    if (!chainRoot_->handle(input)) {
        std::cout << "[Facade] Неизвестная команда: " << input << "\n";
        return false;
    }

    return true;
}

bool GameFacade::createUnit(const std::string& type, int x, int y) {
    return executeCommand(std::make_shared<CreateUnitCommand>(mediator_, type, x, y));
}

bool GameFacade::moveUnit(int unitId, int x, int y) {
    return executeCommand(std::make_shared<MoveUnitCommand>(mediator_, unitId, x, y));
}

bool GameFacade::attack(int attackerId, int targetId) {
    return executeCommand(std::make_shared<AttackCommand>(mediator_, attackerId, targetId));
}

bool GameFacade::collectResource(int unitId, int resourcePointId) {
    return executeCommand(
        std::make_shared<CollectResourceCommand>(mediator_, unitId, resourcePointId));
}

bool GameFacade::heal(int unitId, int buildingId) {
    return executeCommand(std::make_shared<HealCommand>(mediator_, unitId, buildingId));
}

bool GameFacade::buildBuilding(const std::string& buildingType, int x, int y) {
    return executeCommand(
        std::make_shared<BuildBuildingCommand>(mediator_, buildingType, x, y));
}

bool GameFacade::research(const std::string& technologyId) {
    return executeCommand(std::make_shared<ResearchCommand>(mediator_, technologyId));
}

bool GameFacade::distributeResources(const std::string& resourceType,
                                      const std::string& buildingType,
                                      int amount) {
    return executeCommand(std::make_shared<DistributeResourcesCommand>(
        mediator_, resourceType, buildingType, amount));
}

bool GameFacade::produceUnit(const std::string& unitType, int buildingId) {
    return executeCommand(
        std::make_shared<ProduceUnitCommand>(mediator_, unitType, buildingId));
}

void GameFacade::getStats(const std::string& mode) {
    executeCommand(std::make_shared<StatsCommand>(mediator_, mode));
}
