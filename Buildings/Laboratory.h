#pragma once

#include "Building.h"

class Laboratory : public Building {
public:
    Laboratory(int id, int x, int y);
    bool canProduce() const override;
};
