#pragma once

class Unit;

class CombatSystem {
public:
    int calculateDamage(const Unit& attacker, const Unit& target) const;
    int resolveCombat(Unit& attacker, Unit& target);
};
