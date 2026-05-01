# pragma once

#include <cstdint>
#include "HugoSystemMacros.h"

HSYSTEM(PickupSystem)
public:
    void update(uint32_t dt) override;

    void init() override {}
    void onLoad() override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()
