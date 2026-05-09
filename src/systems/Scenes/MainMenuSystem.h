#pragma once

#include "ExitTag.h"
#include "HugoSystemMacros.h"
#include "ResumeTag.h"
#include <cstdint>

HSYSTEM(MainMenuSystem)

    void initResume(ResumeTag& resume);
    void initExit(ExitTag& exit);
public:
    void init() override;
    void onLoad() override;
    void update(uint32_t) override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()
