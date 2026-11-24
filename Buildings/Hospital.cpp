#include "Hospital.h"

Hospital::Hospital(int id, int x, int y)
    : Building(id, "hospital", 150, x, y) {
}

bool Hospital::canProduce() const {
    return false;
}
