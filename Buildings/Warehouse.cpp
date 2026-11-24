#include "Warehouse.h"

Warehouse::Warehouse(int id, int x, int y)
    : Building(id, "warehouse", 180, x, y) {
}

bool Warehouse::canProduce() const {
    return false;
}
