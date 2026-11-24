#pragma once

#include "Building.h"

class Barracks : public Building {
public:
    Barracks(int id, int x, int y);
    bool canProduce() const override;
};
