#pragma once

#include "HugoSystemMacros.h"

#include "AnimationComponent.h"
HSYSTEM(EnemyAnimationSystem)

public:
    void init() override;
    void onLoad() override{};
    void fixedUpdate(uint32_t dt) override{};
    inline void update(uint32_t) override;

    void setIdle(AnimationComponent&);
END_HSYSTEM()