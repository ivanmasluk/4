#include "Barracks.h"

Barracks::Barracks(int id, int x, int y)
    : Building(id, "barracks", 200, x, y) {
}

bool Barracks::canProduce() const {
    return isCompleted();
}
