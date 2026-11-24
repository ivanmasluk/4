#include "Trap.h"
#include "../Units/Unit.h"
#include <sstream>

Trap::Trap(std::shared_ptr<IInteractionStrategy> strategy)
    : strategy_(std::move(strategy)) {
}

void Trap::interact(Unit& unit) {
    std::ostringstream oss;
    oss << "Юнит " << unit.getType() << " (ID=" << unit.getId()
        << ") активировал ловушку";
    logEnv(oss.str());

    if (strategy_) {
        strategy_->apply(unit);
    }
}

char Trap::getSymbol() const {
    return 'T';
}
