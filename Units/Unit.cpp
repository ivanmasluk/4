#include "Unit.h"
#include <algorithm>

int Unit::nextId_ = 1;

Unit::Unit(const Health& health, const Armor& armor, const Attack& attack)
    : id_(nextId_++),
      health_(health),
      armor_(armor),
      attack_(attack),
      maxHealth_(health.getValue()) {
}

int Unit::getId() const {
    return id_;
}

const Health& Unit::getHealth() const {
    return health_;
}

const Armor& Unit::getArmor() const {
    return armor_;
}

const Attack& Unit::getAttack() const {
    return attack_;
}

int Unit::getX() const {
    return x_;
}

int Unit::getY() const {
    return y_;
}

bool Unit::isAlive() const {
    return !health_.isZero();
}

int Unit::getBaseSpeed() const {
    return baseSpeed_;
}

double Unit::getMoveProgress() const {
    return moveProgress_;
}

int Unit::getTerrainDefenseBonus() const {
    return terrainDefenseBonus_;
}

void Unit::setPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Unit::move(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

void Unit::setBaseSpeed(int speed) {
    if (speed < 1) {
        baseSpeed_ = 1;
    } else {
        baseSpeed_ = speed;
    }
}

void Unit::setTerrainDefenseBonus(int bonus) {
    if (bonus < 0) {
        terrainDefenseBonus_ = 0;
    } else {
        terrainDefenseBonus_ = bonus;
    }
}

void Unit::addMoveProgress(double points) {
    if (points < 0) {
        points = 0;
    }
    moveProgress_ += points;
}

void Unit::spendMoveProgress(double cost) {
    if (cost < 0) {
        cost = 0;
    }
    moveProgress_ -= cost;
    if (moveProgress_ < 0) {
        moveProgress_ = 0;
    }
}

void Unit::resetMoveProgress() {
    moveProgress_ = 0;
}

void Unit::takeDamage(int rawDamage) {
    if (rawDamage < 0) {
        rawDamage = 0;
    }

    int actualDamage = armor_.reduceDamage(rawDamage);

    actualDamage -= terrainDefenseBonus_;
    if (actualDamage < 0) {
        actualDamage = 0;
    }

    health_.decrease(actualDamage);

    UnitEvent damagedEvent{
        UnitEventType::Damaged,
        id_,
        getType(),
        actualDamage
    };
    notify(damagedEvent);

    if (health_.isZero()) {
        UnitEvent destroyedEvent{
            UnitEventType::Destroyed,
            id_,
            getType(),
            actualDamage
        };
        notify(destroyedEvent);
        clearObservers();
    }
}

void Unit::boostAttack(int amount) {
    if (amount < 0) {
        amount = 0;
    }
    attack_.setValue(attack_.getValue() + amount);
}

void Unit::fullHeal() {
    health_.setValue(maxHealth_);
}

void Unit::subscribe(IObserver* observer) {
    if (observer == nullptr) {
        return;
    }
    if (std::find(observers_.begin(), observers_.end(), observer) == observers_.end()) {
        observers_.push_back(observer);
    }
}

void Unit::unsubscribe(IObserver* observer) {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void Unit::clearObservers() {
    observers_.clear();
}

void Unit::notify(const UnitEvent& event) {
    std::vector<IObserver*> snapshot = observers_;
    for (IObserver* observer : snapshot) {
        if (observer != nullptr) {
            observer->onUnitEvent(event);
        }
    }
}

#include <ostream>

std::ostream& operator<<(std::ostream& os, const Unit& unit) {
    os << unit.getType()
       << " (ID=" << unit.getId() << ")"
       << " at (" << unit.getX() << "," << unit.getY() << ")"
       << " HP=" << unit.getHealth().getValue()
       << " ATK=" << unit.getAttack().getValue();
    return os;
}
