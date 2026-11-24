#pragma once

#include "Building.h"

class Warehouse : public Building {
public:
    Warehouse(int id, int x, int y);
    bool canProduce() const override;
};
