#pragma once

#include "HugoSystemMacros.h"

#include <cstdint>

#include "ResumeTag.h"
#include "ExitTag.h"
#include "ClockTag.h"
#include "EnemyTag.h"

HSYSTEM(LoseSceneSystem)
    void initResume(ResumeTag& resume);
    void initExit(ExitTag& exit);
    void initTime(ClockTag& time);
    void initEnemyCount(EnemyTag& count);
public:
    void init() override;
    void onLoad() override;
    void update(uint32_t) override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()
