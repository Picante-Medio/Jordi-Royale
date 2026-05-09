#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(AudioEventsSystem)
public:
    void init() override;
    void onLoad() override;
    inline void update(uint32_t dt) override;

    void fixedUpdate(uint32_t) override {};
END_HSYSTEM()
