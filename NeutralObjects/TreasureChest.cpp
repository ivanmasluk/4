#include "TreasureChest.h"
#include "../Units/Unit.h"
#include <sstream>

TreasureChest::TreasureChest(std::shared_ptr<IInteractionStrategy> strategy)
    : strategy_(std::move(strategy)) {
}

void TreasureChest::interact(Unit& unit) {
    std::ostringstream oss;
    oss << "Юнит " << unit.getType() << " (ID=" << unit.getId()
        << ") открыл сундук";
    logEnv(oss.str());

    if (strategy_) {
        strategy_->apply(unit);
    }
}

char TreasureChest::getSymbol() const {
    return 'C';
}
