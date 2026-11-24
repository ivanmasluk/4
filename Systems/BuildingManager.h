#pragma once

#include "../Buildings/Building.h"
#include <memory>
#include <string>
#include <vector>

class BuildingManager {
private:
    std::vector<std::shared_ptr<Building>> buildings_;
    int nextId_ = 1;
    std::string activeResearch_;
    int researchTurnsLeft_ = 0;

public:
    bool buildBuilding(const std::string& type, int x, int y);
    bool startResearch(const std::string& technologyId);
    bool produceUnit(const std::string& unitType, int buildingId);
    Building* getBuildingById(int id);
    const std::vector<std::shared_ptr<Building>>& getBuildings() const;
    void tickResearch();
    void print() const;
};
