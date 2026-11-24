#include "EnergySource.h"
#include "../Units/Unit.h"
#include <sstream>

EnergySource::EnergySource(std::shared_ptr<IInteractionStrategy> strategy)
    : strategy_(std::move(strategy)) {
}

void EnergySource::interact(Unit& unit) {
    std::ostringstream oss;
    oss << "Юнит " << unit.getType() << " (ID=" << unit.getId()
        << ") использовал источник энергии";
    logEnv(oss.str());

    if (strategy_) {
        strategy_->apply(unit);
    }
}

char EnergySource::getSymbol() const {
    return 'E';
}
