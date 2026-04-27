#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(ProgressionSystem)

    // time for clock
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int miliseconds = 0;

public:

    void onLoad() override;
    void init() override;

    void update(uint32_t dt) override;
    void fixedUpdate(uint32_t) override;
END_HSYSTEM()