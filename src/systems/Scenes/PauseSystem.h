#pragma once
#include "HUGO.h"

#include "ResumeTag.h"

HSYSTEM(PauseSystem)

    void initButtons(ResumeTag& resume);

public:

    void onLoad() override;
    void init() override;

    void update(uint32_t) override;
    void fixedUpdate(uint32_t) override;
    
END_HSYSTEM()