#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(AliOliSystem)

    float damage = 5.f;
    HUGO::Int count = 1;

    bool active = false;
public:
    void init() override;
    void onLoad() override;

    void fixedUpdate(uint32_t dt) override;
    void update(uint32_t) override;
END_HSYSTEM()