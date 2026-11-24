#include "GameMediator.h"
#include "../Base/Base.h"
#include "../GameField.h"
#include "../Terrain/TerrainMap.h"
#include "../Systems/UnitManager.h"
#include "../Systems/BuildingManager.h"
#include "../Systems/ResourceSystem.h"
#include "../Systems/CombatSystem.h"
#include "../Units/Unit.h"
#include "../Buildings/Building.h"
#include "../Logging/ILogger.h"
#include "../Logging/LogEvent.h"
#include <iostream>
#include <sstream>

GameMediator::GameMediator(std::shared_ptr<Base> base,
                           std::shared_ptr<GameField> field,
                           std::shared_ptr<TerrainMap> terrainMap,
                           std::shared_ptr<UnitManager> unitManager,
                           std::shared_ptr<BuildingManager> buildingManager,
                           std::shared_ptr<ResourceSystem> resourceSystem,
                           std::shared_ptr<CombatSystem> combatSystem)
    : base_(std::move(base)),
      field_(std::move(field)),
      terrainMap_(std::move(terrainMap)),
      unitManager_(std::move(unitManager)),
      buildingManager_(std::move(buildingManager)),
      resourceSystem_(std::move(resourceSystem)),
      combatSystem_(std::move(combatSystem)) {
}

void GameMediator::setLogger(std::shared_ptr<ILogger> logger) {
    logger_ = std::move(logger);
}

void GameMediator::log(const std::string& level,
                       const std::string& source,
                       const std::string& message) {
    if (logger_ == nullptr) {
        return;
    }
    logger_->log(LogEvent(level, source, message));
}

bool GameMediator::createUnit(const std::string& type, int x, int y) {
    if (!resourceSystem_->spendResources("metal", 10)) {
        std::cout << "[Mediator] Недостаточно metal для юнита\n";
        return false;
    }

    if (!unitManager_->createUnit(type, x, y)) {
        resourceSystem_->addResources("metal", 10);
        return false;
    }

    Unit* created = field_->getUnit(x, y);
    int createdId = 0;
    if (created != nullptr) {
        createdId = created->getId();
    }

    notifyUnitCreated(createdId, type);
    return true;
}

bool GameMediator::moveUnit(int unitId, int x, int y) {
    Unit* unit = unitManager_->getUnitById(unitId);
    if (unit == nullptr) {
        std::cout << "[Mediator] Юнит для перемещения не найден\n";
        return false;
    }

    int fromX = unit->getX();
    int fromY = unit->getY();
    std::string unitType = unit->getType();

    if (!unitManager_->moveUnit(unitId, x, y, *terrainMap_)) {
        return false;
    }

    std::ostringstream oss;
    oss << unitType << " (ID=" << unitId << ") перемещён с ("
        << fromX << "," << fromY << ") на (" << x << "," << y << ")";
    log("INFO", "UNIT", oss.str());
    return true;
}

bool GameMediator::resolveCombat(int attackerId, int targetId) {
    Unit* attacker = unitManager_->getUnitById(attackerId);
    Unit* target = unitManager_->getUnitById(targetId);

    if (attacker == nullptr || target == nullptr) {
        std::cout << "[Mediator] Атакующий или цель не найдены\n";
        return false;
    }

    std::string attackerType = attacker->getType();
    std::string targetType = target->getType();

    int damage = combatSystem_->resolveCombat(*attacker, *target);
    notifyCombatResolved(attackerId, targetId, damage);

    int targetHp = target->getHealth().getValue();

    std::ostringstream combatOss;
    combatOss << attackerType << " (ID=" << attackerId << ") наносит "
              << damage << " урона " << targetType << " (ID=" << targetId
              << "), HP " << targetHp;
    log("INFO", "COMBAT", combatOss.str());

    if (!target->isAlive()) {
        std::ostringstream alertOss;
        alertOss << "Юнит " << targetType << " (ID=" << targetId << ") уничтожен";
        log("ALERT", "COMBAT", alertOss.str());
        unitManager_->removeUnit(targetId);
    }

    return true;
}

bool GameMediator::collectResource(int unitId, int resourcePointId) {
    Unit* unit = unitManager_->getUnitById(unitId);
    if (unit == nullptr) {
        std::cout << "[Mediator] Юнит для сбора не найден\n";
        return false;
    }

    std::string resourceType;
    int amount = 25;

    if (resourcePointId == 1) {
        resourceType = "wood";
    } else if (resourcePointId == 2) {
        resourceType = "metal";
    } else if (resourcePointId == 3) {
        resourceType = "energy";
    } else {
        std::cout << "[Mediator] Неизвестная ресурсная точка id="
                  << resourcePointId
                  << " (доступны: 1=wood, 2=metal, 3=energy)\n";
        return false;
    }

    resourceSystem_->addResources(resourceType, amount);
    notifyResourceCollected(amount, resourceType);

    std::ostringstream oss;
    oss << unit->getType() << " (ID=" << unitId << ") собирает "
        << amount << " " << resourceType;
    log("INFO", "UNIT", oss.str());
    return true;
}

bool GameMediator::healUnit(int unitId, int buildingId) {
    Unit* unit = unitManager_->getUnitById(unitId);
    Building* building = buildingManager_->getBuildingById(buildingId);

    if (unit == nullptr) {
        std::cout << "[Mediator] Юнит не найден\n";
        return false;
    }

    if (building == nullptr || building->getType() != "hospital") {
        std::cout << "[Mediator] Нужен hospital\n";
        return false;
    }

    unit->fullHeal();
    std::cout << "[Mediator] Юнит id=" << unitId << " вылечен\n";

    std::ostringstream oss;
    oss << unit->getType() << " (ID=" << unitId << ") полностью вылечен в hospital (ID="
        << buildingId << ")";
    log("INFO", "UNIT", oss.str());
    return true;
}

bool GameMediator::buildBuilding(const std::string& buildingType, int x, int y) {
    if (!resourceSystem_->spendResources("wood", 20)) {
        std::cout << "[Mediator] Недостаточно wood для здания\n";
        return false;
    }

    if (!buildingManager_->buildBuilding(buildingType, x, y)) {
        resourceSystem_->addResources("wood", 20);
        return false;
    }

    Building* b = nullptr;
    const auto& all = buildingManager_->getBuildings();
    if (!all.empty()) {
        b = all.back().get();
    }
    if (b != nullptr) {
        notifyBuildingCompleted(b->getId(), b->getType());
    }
    return true;
}

bool GameMediator::startResearch(const std::string& technologyId) {
    if (!resourceSystem_->spendResources("energy", 15)) {
        std::cout << "[Mediator] Недостаточно energy для исследования\n";
        return false;
    }

    if (!buildingManager_->startResearch(technologyId)) {
        resourceSystem_->addResources("energy", 15);
        return false;
    }

    std::ostringstream oss;
    oss << "Исследование '" << technologyId << "' запущено";
    log("INFO", "BASE", oss.str());
    return true;
}

bool GameMediator::distributeResources(const std::string& resourceType,
                                       const std::string& buildingType,
                                       int amount) {
    bool hasBuilding = false;
    for (const auto& b : buildingManager_->getBuildings()) {
        if (b->getType() == buildingType) {
            hasBuilding = true;
            break;
        }
    }

    if (!hasBuilding) {
        std::cout << "[Mediator] Нет зданий типа " << buildingType << "\n";
        return false;
    }

    if (!resourceSystem_->distribute(resourceType, buildingType, amount)) {
        std::cout << "[Mediator] Не удалось распределить ресурсы\n";
        return false;
    }

    std::cout << "[Mediator] Распределено " << amount << " "
              << resourceType << " для типа зданий " << buildingType
              << "\n";

    std::ostringstream oss;
    oss << "Распределено " << amount << " " << resourceType
        << " для зданий типа " << buildingType;
    log("INFO", "BASE", oss.str());
    return true;
}

bool GameMediator::produceUnit(const std::string& unitType, int buildingId) {
    if (!buildingManager_->produceUnit(unitType, buildingId)) {
        return false;
    }

    Building* b = buildingManager_->getBuildingById(buildingId);
    if (b == nullptr) {
        return false;
    }

    std::ostringstream oss;
    oss << "Производство юнита " << unitType << " в здании ID=" << buildingId;
    log("INFO", "BASE", oss.str());

    return createUnit(unitType, b->getX(), b->getY());
}

void GameMediator::getStats(const std::string& mode) {
    if (mode == "all" || mode == "resources") {
        resourceSystem_->print();
    }
    if (mode == "all" || mode == "units") {
        unitManager_->printUnits();
    }
    if (mode == "all" || mode == "buildings") {
        buildingManager_->print();
    }
    if (mode == "all") {
        std::cout << "База: hp=" << base_->getHealth()
                  << " living=" << base_->getLivingUnits()
                  << " resources(base)=" << base_->getResources()
                  << "\n";
    }
}

void GameMediator::notifyUnitCreated(int unitId, const std::string& type) {
    std::cout << "[Mediator][notify] unit created type=" << type
              << " id=" << unitId << "\n";

    std::ostringstream oss;
    oss << "Создан юнит " << type << " (ID=" << unitId << ")";
    log("INFO", "BASE", oss.str());
}

void GameMediator::notifyResourceCollected(int amount, const std::string& resourceType) {
    std::cout << "[Mediator][notify] collected " << amount
              << " " << resourceType << "\n";
}

void GameMediator::notifyCombatResolved(int attackerId, int targetId, int damage) {
    std::cout << "[Mediator][notify] combat attacker=" << attackerId
              << " target=" << targetId
              << " damage=" << damage << "\n";
}

void GameMediator::notifyBuildingCompleted(int buildingId, const std::string& type) {
    std::cout << "[Mediator][notify] building ready id=" << buildingId
              << " type=" << type << "\n";

    std::ostringstream oss;
    oss << "Построено здание " << type << " (ID=" << buildingId << ")";
    log("INFO", "BASE", oss.str());
}

void GameMediator::notifyResearchCompleted(const std::string& technologyId) {
    std::cout << "[Mediator][notify] research done: " << technologyId << "\n";

    std::ostringstream oss;
    oss << "Исследование '" << technologyId << "' завершено";
    log("INFO", "BASE", oss.str());
}

std::shared_ptr<Base> GameMediator::getBase() const {
    return base_;
}

std::shared_ptr<GameField> GameMediator::getField() const {
    return field_;
}

std::shared_ptr<TerrainMap> GameMediator::getTerrainMap() const {
    return terrainMap_;
}

std::shared_ptr<UnitManager> GameMediator::getUnitManager() const {
    return unitManager_;
}

std::shared_ptr<BuildingManager> GameMediator::getBuildingManager() const {
    return buildingManager_;
}

std::shared_ptr<ResourceSystem> GameMediator::getResourceSystem() const {
    return resourceSystem_;
}

std::shared_ptr<CombatSystem> GameMediator::getCombatSystem() const {
    return combatSystem_;
}
