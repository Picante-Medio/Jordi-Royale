#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(AliOliSystem)

    HUGO::Float damage = 5.f;
    HUGO::Int count = 1;

    HUGO::Bool active = false;
public:
    void init() override;
    void onLoad() override;

    void fixedUpdate(uint32_t dt) override;
    void update(uint32_t) override;
END_HSYSTEM()