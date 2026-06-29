#pragma once

#include "HugoSystemMacros.h"

struct ResumeTag;

HSYSTEM(UpgradeSystem)
    void resumeGame(ResumeTag& tag);
public:
    void init() override;
    void onLoad() override;

    void fixedUpdate(uint32_t) override;
    void update(uint32_t dt) override; 
END_HSYSTEM()
