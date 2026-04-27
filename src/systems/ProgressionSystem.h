#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(ProgressionSystem)



public:

    void onLoad() override;
    void init() override;

    void update(uint32_t dt) override;
    void fixedUpdate(uint32_t) override;
END_HSYSTEM()