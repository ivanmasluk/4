#include "Laboratory.h"

Laboratory::Laboratory(int id, int x, int y)
    : Building(id, "laboratory", 120, x, y) {
}

bool Laboratory::canProduce() const {
    return false;
}
