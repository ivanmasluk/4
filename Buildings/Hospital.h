#pragma once

#include "Building.h"

class Hospital : public Building {
public:
    Hospital(int id, int x, int y);
    bool canProduce() const override;
};
