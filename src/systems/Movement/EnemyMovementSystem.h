#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(EnemyMovementSystem)
public:
    void init() override;
    void onLoad() override;
    void fixedUpdate(uint32_t dt) override;
    inline void update(uint32_t) override {};
END_HSYSTEM()
