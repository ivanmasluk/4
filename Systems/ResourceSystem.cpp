#include "ResourceSystem.h"
#include <iostream>

ResourceSystem::ResourceSystem(int wood, int metal, int energy)
    : wood_(wood), metal_(metal), energy_(energy) {
}

int ResourceSystem::getWood() const {
    return wood_;
}

int ResourceSystem::getMetal() const {
    return metal_;
}

int ResourceSystem::getEnergy() const {
    return energy_;
}

int ResourceSystem::getAllocated(const std::string& buildingType) const {
    auto it = allocatedToBuildingType_.find(buildingType);
    if (it == allocatedToBuildingType_.end()) {
        return 0;
    }
    return it->second;
}

void ResourceSystem::addResources(const std::string& type, int amount) {
    if (amount < 0) {
        amount = 0;
    }

    if (type == "wood") {
        wood_ += amount;
    } else if (type == "metal") {
        metal_ += amount;
    } else if (type == "energy") {
        energy_ += amount;
    }
}

bool ResourceSystem::spendResources(const std::string& type, int amount) {
    if (amount < 0) {
        return false;
    }

    if (type == "wood") {
        if (wood_ < amount) {
            return false;
        }
        wood_ -= amount;
        return true;
    }

    if (type == "metal") {
        if (metal_ < amount) {
            return false;
        }
        metal_ -= amount;
        return true;
    }

    if (type == "energy") {
        if (energy_ < amount) {
            return false;
        }
        energy_ -= amount;
        return true;
    }

    return false;
}

bool ResourceSystem::distribute(const std::string& resourceType,
                                const std::string& buildingType,
                                int amount) {
    if (!spendResources(resourceType, amount)) {
        return false;
    }

    allocatedToBuildingType_[buildingType] += amount;
    return true;
}

void ResourceSystem::print() const {
    std::cout << "Ресурсы: wood=" << wood_
              << " metal=" << metal_
              << " energy=" << energy_ << "\n";

    if (!allocatedToBuildingType_.empty()) {
        std::cout << "Распределено по типам зданий:\n";
        for (const auto& item : allocatedToBuildingType_) {
            std::cout << "  " << item.first << ": " << item.second << "\n";
        }
    }
}
