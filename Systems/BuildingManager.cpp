#include "BuildingManager.h"
#include "../Buildings/Barracks.h"
#include "../Buildings/Hospital.h"
#include "../Buildings/Laboratory.h"
#include "../Buildings/Warehouse.h"
#include <iostream>

bool BuildingManager::buildBuilding(const std::string& type, int x, int y) {
    std::shared_ptr<Building> building;

    if (type == "barracks") {
        building = std::make_shared<Barracks>(nextId_, x, y);
    } else if (type == "hospital") {
        building = std::make_shared<Hospital>(nextId_, x, y);
    } else if (type == "laboratory") {
        building = std::make_shared<Laboratory>(nextId_, x, y);
    } else if (type == "warehouse") {
        building = std::make_shared<Warehouse>(nextId_, x, y);
    } else {
        std::cout << "[BuildingManager] Неизвестный тип здания: " << type << "\n";
        return false;
    }

    ++nextId_;
    buildings_.push_back(building);
    std::cout << "[BuildingManager] Построено " << type
              << " id=" << building->getId()
              << " at (" << x << "," << y << ")\n";
    return true;
}

bool BuildingManager::startResearch(const std::string& technologyId) {
    bool hasLab = false;
    for (const auto& b : buildings_) {
        if (b->getType() == "laboratory" && b->isCompleted()) {
            hasLab = true;
            break;
        }
    }

    if (!hasLab) {
        std::cout << "[BuildingManager] Нужна laboratory\n";
        return false;
    }

    if (!activeResearch_.empty()) {
        std::cout << "[BuildingManager] Уже идёт исследование: "
                  << activeResearch_ << "\n";
        return false;
    }

    activeResearch_ = technologyId;
    researchTurnsLeft_ = 3;
    std::cout << "[BuildingManager] Исследование начато: "
              << technologyId << " (ходов: 3)\n";
    return true;
}

bool BuildingManager::produceUnit(const std::string& unitType, int buildingId) {
    Building* building = getBuildingById(buildingId);
    if (building == nullptr) {
        std::cout << "[BuildingManager] Здание не найдено\n";
        return false;
    }

    if (building->getType() != "barracks") {
        std::cout << "[BuildingManager] Производство только в barracks\n";
        return false;
    }

    if (!building->canProduce()) {
        std::cout << "[BuildingManager] Здание не готово\n";
        return false;
    }

    std::cout << "[BuildingManager] Заказано производство "
              << unitType << " в barracks id=" << buildingId << "\n";
    return true;
}

Building* BuildingManager::getBuildingById(int id) {
    for (auto& b : buildings_) {
        if (b->getId() == id) {
            return b.get();
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Building>>& BuildingManager::getBuildings() const {
    return buildings_;
}

void BuildingManager::tickResearch() {
    if (activeResearch_.empty()) {
        return;
    }

    if (researchTurnsLeft_ > 0) {
        --researchTurnsLeft_;
    }

    if (researchTurnsLeft_ == 0) {
        std::cout << "[BuildingManager] Исследование завершено: "
                  << activeResearch_ << "\n";
        activeResearch_.clear();
    }
}

void BuildingManager::print() const {
    std::cout << "Здания (" << buildings_.size() << "):\n";
    for (const auto& b : buildings_) {
        std::cout << "  id=" << b->getId()
                  << " type=" << b->getType()
                  << " hp=" << b->getHealth()
                  << " pos=(" << b->getX() << "," << b->getY() << ")"
                  << " ready=" << (b->isCompleted() ? "yes" : "no")
                  << "\n";
    }

    if (!activeResearch_.empty()) {
        std::cout << "Исследование: " << activeResearch_
                  << " (осталось ходов: " << researchTurnsLeft_ << ")\n";
    }
}
