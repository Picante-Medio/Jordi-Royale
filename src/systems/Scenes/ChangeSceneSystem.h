#pragma once

#include <cstdint>
#include "HugoSystemMacros.h"

HSYSTEM(ChangeSceneSystem)
public:
    void init() override;
    void update(uint32_t) override;

    void onLoad() override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()

