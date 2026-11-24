#pragma once

#include <memory>
#include <string>

class Base;
class GameField;
class TerrainMap;
class UnitManager;
class BuildingManager;
class ResourceSystem;
class CombatSystem;
class ILogger;

class GameMediator {
private:
    std::shared_ptr<Base> base_;
    std::shared_ptr<GameField> field_;
    std::shared_ptr<TerrainMap> terrainMap_;
    std::shared_ptr<UnitManager> unitManager_;
    std::shared_ptr<BuildingManager> buildingManager_;
    std::shared_ptr<ResourceSystem> resourceSystem_;
    std::shared_ptr<CombatSystem> combatSystem_;
    std::shared_ptr<ILogger> logger_;

    void log(const std::string& level,
             const std::string& source,
             const std::string& message);

public:
    GameMediator(std::shared_ptr<Base> base,
                 std::shared_ptr<GameField> field,
                 std::shared_ptr<TerrainMap> terrainMap,
                 std::shared_ptr<UnitManager> unitManager,
                 std::shared_ptr<BuildingManager> buildingManager,
                 std::shared_ptr<ResourceSystem> resourceSystem,
                 std::shared_ptr<CombatSystem> combatSystem);

    void setLogger(std::shared_ptr<ILogger> logger);

    bool createUnit(const std::string& type, int x, int y);
    bool moveUnit(int unitId, int x, int y);
    bool resolveCombat(int attackerId, int targetId);
    bool collectResource(int unitId, int resourcePointId);
    bool healUnit(int unitId, int buildingId);
    bool buildBuilding(const std::string& buildingType, int x, int y);
    bool startResearch(const std::string& technologyId);
    bool distributeResources(const std::string& resourceType,
                             const std::string& buildingType,
                             int amount);
    bool produceUnit(const std::string& unitType, int buildingId);
    void getStats(const std::string& mode);

    void notifyUnitCreated(int unitId, const std::string& type);
    void notifyResourceCollected(int amount, const std::string& resourceType);
    void notifyCombatResolved(int attackerId, int targetId, int damage);
    void notifyBuildingCompleted(int buildingId, const std::string& type);
    void notifyResearchCompleted(const std::string& technologyId);

    std::shared_ptr<Base> getBase() const;
    std::shared_ptr<GameField> getField() const;
    std::shared_ptr<TerrainMap> getTerrainMap() const;
    std::shared_ptr<UnitManager> getUnitManager() const;
    std::shared_ptr<BuildingManager> getBuildingManager() const;
    std::shared_ptr<ResourceSystem> getResourceSystem() const;
    std::shared_ptr<CombatSystem> getCombatSystem() const;
};
