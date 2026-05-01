#pragma once

#include "HUGO.h"

// PROVISIONAL SYSTEM TO TRY THE GAME LOGIC WHILE THE CHATS AREN'T WORKING

HSYSTEM(PauseInitSystem)

public:
    void onLoad() override;
    void init() override;

    void update(uint32_t) override;
    void fixedUpdate(uint32_t) override;
END_HSYSTEM()