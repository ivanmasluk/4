#pragma once

#include <functional>
#include <memory>
#include <string>

class GameField;
class Base;
class Unit;
class TerrainMap;

class UnitManager {
public:
    using CreateUnitFn = std::function<bool(const std::string& type, int x, int y)>;

private:
    std::shared_ptr<GameField> field_;
    std::shared_ptr<Base> base_;
    CreateUnitFn createFn_;

public:
    UnitManager(std::shared_ptr<GameField> field,
                std::shared_ptr<Base> base);

    void setCreateUnitFunction(CreateUnitFn fn);

    bool createUnit(const std::string& type, int x, int y);
    bool moveUnit(int unitId, int x, int y, TerrainMap& terrainMap);
    Unit* getUnitById(int unitId);
    bool removeUnit(int unitId);
    void printUnits();
};
