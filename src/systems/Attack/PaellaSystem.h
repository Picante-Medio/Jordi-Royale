#pragma once

#include "EcsTypes.h"
#include "HugoSystemMacros.h"
#include <array>
#include <cstdint>

const unsigned short int MAX_PAELLA = 10;

HSYSTEM(PaellaSystem)
    unsigned short int count = 0;
    unsigned int extraDamage = 0;
    float cooldown = 1.f;

    bool active = false;

    EntityID pivot;
    std::array<EntityID, MAX_PAELLA> paellas;
public:
    void init() override;
    void onLoad() override;
    void update(uint32_t dt) override;
    void fixedUpdate(uint32_t dt) override;
END_HSYSTEM()
