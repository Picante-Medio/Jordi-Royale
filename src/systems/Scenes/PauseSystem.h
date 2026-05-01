#pragma once
#include "HUGO.h"

#include "ResumeTag.h"
#include "ExitTag.h"

HSYSTEM(PauseSystem)

    void initResume(ResumeTag& resume);
    void initExit(ExitTag& exit);

public:

    void onLoad() override;
    void init() override;

    void update(uint32_t) override;
    void fixedUpdate(uint32_t) override;
    
END_HSYSTEM()