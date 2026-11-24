#include "Building.h"

Building::Building(int id, const std::string& type, int health, int x, int y)
    : id_(id),
      type_(type),
      health_(health),
      x_(x),
      y_(y),
      buildProgress_(100),
      completed_(true) {
}

int Building::getId() const {
    return id_;
}

const std::string& Building::getType() const {
    return type_;
}

int Building::getHealth() const {
    return health_;
}

int Building::getX() const {
    return x_;
}

int Building::getY() const {
    return y_;
}

int Building::getBuildProgress() const {
    return buildProgress_;
}

bool Building::isCompleted() const {
    return completed_;
}

void Building::update() {
}

bool Building::canProduce() const {
    return completed_;
}
