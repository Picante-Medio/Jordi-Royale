#pragma once

#include "HugoSystemMacros.h"

#include <cstdint>

#include "ResumeTag.h"
#include "ExitTag.h"

HSYSTEM(MainMenuSystem)
    void initResume(ResumeTag& resume);
    void initExit(ExitTag& exit);
public:
    void init() override;
    void onLoad() override;
    void update(uint32_t) override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()
