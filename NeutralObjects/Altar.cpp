#include "Altar.h"
#include "../Units/Unit.h"
#include "../Units/UnitTypeInfo.h"
#include "../Strategies/AttackBoostStrategy.h"
#include "../Strategies/HealthRestoreStrategy.h"
#include <iostream>
#include <sstream>

Altar::Altar()
    : defaultStrategy_(std::make_shared<AttackBoostStrategy>(10)) {
}

Altar::Altar(std::shared_ptr<IInteractionStrategy> defaultStrategy)
    : defaultStrategy_(std::move(defaultStrategy)) {
}

void Altar::interact(Unit& unit) {
    const auto unitType = unitTypeFromString(unit.getType());
    std::shared_ptr<IInteractionStrategy> strategy = defaultStrategy_;

    if (unitType.has_value()) {
        const UnitTypeInfo& info = getUnitTypeInfo(*unitType);

        if (info.category == UnitCategory::Infantry) {
            strategy = std::make_shared<AttackBoostStrategy>(15);
            std::cout << "[Altar] Пехота: стратегия усиления атаки\n";
        } else if (info.category == UnitCategory::Archer) {
            strategy = std::make_shared<AttackBoostStrategy>(8);
            std::cout << "[Altar] Лучник: стратегия усиления атаки (меньший бонус)\n";
        } else if (info.category == UnitCategory::Cavalry) {
            strategy = std::make_shared<HealthRestoreStrategy>();
            std::cout << "[Altar] Конница: стратегия восстановления здоровья\n";
        }
    }

    std::ostringstream oss;
    oss << "Юнит " << unit.getType() << " (ID=" << unit.getId()
        << ") активировал алтарь";
    logEnv(oss.str());

    if (strategy) {
        strategy->apply(unit);
    }
}

char Altar::getSymbol() const {
    return 'A';
}
