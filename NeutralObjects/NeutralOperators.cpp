#include "NeutralOperators.h"
#include "../Logging/ILogger.h"
#include <sstream>

namespace {
std::shared_ptr<ILogger> g_neutralLogger;
}

void setNeutralLogger(std::shared_ptr<ILogger> logger) {
    g_neutralLogger = std::move(logger);
}

Unit& operator+(Unit& unit, TreasureChest& chest) {
    if (chest.getLogger() == nullptr && g_neutralLogger != nullptr) {
        chest.setLogger(g_neutralLogger);
    }
    chest.interact(unit);
    return unit;
}

Unit& operator-(Unit& unit, Trap& trap) {
    if (trap.getLogger() == nullptr && g_neutralLogger != nullptr) {
        trap.setLogger(g_neutralLogger);
    }
    trap.interact(unit);
    return unit;
}

Unit& operator*(Unit& unit, Altar& altar) {
    if (altar.getLogger() == nullptr && g_neutralLogger != nullptr) {
        altar.setLogger(g_neutralLogger);
    }
    altar.interact(unit);
    return unit;
}

Unit& operator/(Unit& unit, EnergySource& source) {
    if (source.getLogger() == nullptr && g_neutralLogger != nullptr) {
        source.setLogger(g_neutralLogger);
    }
    source.interact(unit);
    return unit;
}
