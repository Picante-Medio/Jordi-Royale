#pragma once

#include "HugoSystemMacros.h"
#include "HPComponent.h"
#include "LevelComponent.h"

HSYSTEM(StatSystem)
    void updateHPText(HPComponent& hp);
    void updateXPText(LevelComponent& xp);

public:
    void onLoad() override;
    void init() override;

    void update(uint32_t) override;
    void fixedUpdate(uint32_t) override;
END_HSYSTEM()