#include "UnitManager.h"
#include "../GameField.h"
#include "../Base/Base.h"
#include "../Terrain/TerrainMap.h"
#include "../Units/Unit.h"
#include <iostream>

UnitManager::UnitManager(std::shared_ptr<GameField> field,
                         std::shared_ptr<Base> base)
    : field_(std::move(field)),
      base_(std::move(base)) {
}

void UnitManager::setCreateUnitFunction(CreateUnitFn fn) {
    createFn_ = std::move(fn);
}

bool UnitManager::createUnit(const std::string& type, int x, int y) {
    if (!createFn_) {
        std::cout << "[UnitManager] Функция создания не задана\n";
        return false;
    }
    return createFn_(type, x, y);
}

bool UnitManager::moveUnit(int unitId, int x, int y, TerrainMap& terrainMap) {
    Unit* unit = getUnitById(unitId);
    if (unit == nullptr) {
        std::cout << "[UnitManager] Юнит id=" << unitId << " не найден\n";
        return false;
    }

    const int fromX = unit->getX();
    const int fromY = unit->getY();

    if (!field_->moveUnit(fromX, fromY, x, y, terrainMap)) {
        std::cout << "[UnitManager] Не удалось переместить юнита id="
                  << unitId << "\n";
        return false;
    }

    std::cout << "[UnitManager] Юнит id=" << unitId
              << " перемещён в (" << x << "," << y << ")\n";
    return true;
}

Unit* UnitManager::getUnitById(int unitId) {
    for (auto& unit : *field_) {
        if (unit.getId() == unitId) {
            return &unit;
        }
    }
    return nullptr;
}

bool UnitManager::removeUnit(int unitId) {
    Unit* unit = getUnitById(unitId);
    if (unit == nullptr) {
        return false;
    }
    return field_->removeUnit(unit->getX(), unit->getY());
}

void UnitManager::printUnits() {
    std::cout << "Юниты (" << field_->getUnitCount() << "):\n";
    for (auto& unit : *field_) {
        std::cout << "  id=" << unit.getId()
                  << " type=" << unit.getType()
                  << " hp=" << unit.getHealth().getValue()
                  << " armor=" << unit.getArmor().getValue()
                  << " atk=" << unit.getAttack().getValue()
                  << " pos=(" << unit.getX() << "," << unit.getY() << ")"
                  << "\n";
    }
}
