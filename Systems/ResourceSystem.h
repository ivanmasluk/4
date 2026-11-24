#pragma once

#include <map>
#include <string>

class ResourceSystem {
private:
    int wood_;
    int metal_;
    int energy_;
    std::map<std::string, int> allocatedToBuildingType_;

public:
    ResourceSystem(int wood = 100, int metal = 100, int energy = 100);

    int getWood() const;
    int getMetal() const;
    int getEnergy() const;
    int getAllocated(const std::string& buildingType) const;

    void addResources(const std::string& type, int amount);
    bool spendResources(const std::string& type, int amount);
    bool distribute(const std::string& resourceType,
                    const std::string& buildingType,
                    int amount);
    void print() const;
};
