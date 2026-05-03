#pragma once

#include "EcsTypes.h"
#include "HugoSystemMacros.h"

HSYSTEM(LevelingSystem)

    unsigned long int experienceIncrement = 100;
    EntityID player;

public:

    void onLoad() override;
    void init() override;

    void update(uint32_t) override;
    void fixedUpdate(uint32_t) override;

END_HSYSTEM()
