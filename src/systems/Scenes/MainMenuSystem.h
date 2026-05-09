#pragma once

#include "HUGO.h"
#include <cstdint>

HSYSTEM(MainMenuSystem)

public:
    void init() override {}
    void onLoad() override;
    void update(uint32_t) override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()
