#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(MusicSystem)
public:
    void onLoad() override;
    void init() override;

    void update(uint32_t) override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()