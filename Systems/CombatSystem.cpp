#include "CombatSystem.h"
#include "../Units/Unit.h"

int CombatSystem::calculateDamage(const Unit& attacker, const Unit& target) const {
    int raw = attacker.getAttack().getValue();
    int afterArmor = target.getArmor().reduceDamage(raw);
    int bonus = target.getTerrainDefenseBonus();
    int result = afterArmor - bonus;
    if (result < 0) {
        result = 0;
    }
    return result;
}

int CombatSystem::resolveCombat(Unit& attacker, Unit& target) {
    const int hpBefore = target.getHealth().getValue();
    target.takeDamage(attacker.getAttack().getValue());
    const int hpAfter = target.getHealth().getValue();
    int dealt = hpBefore - hpAfter;
    if (dealt < 0) {
        dealt = 0;
    }
    return dealt;
}
