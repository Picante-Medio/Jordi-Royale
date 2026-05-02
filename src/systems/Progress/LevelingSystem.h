#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(LevelingSystem)

    float grabDistance = 5.f;
    unsigned long int experienceIncrement = 100;

public:

    void onLoad() override;
    void init() override;

    void update(uint32_t) override;
    void fixedUpdate(uint32_t) override;

END_HSYSTEM()
