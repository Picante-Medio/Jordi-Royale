#pragma once

#include "HugoSystemMacros.h"
#include "HugoMath.h"

HSYSTEM(PlayerMovementSystem)

HUGO::Vector2 lastMousePosition;

public:
void init() override;
void onLoad() override;

void update(uint32_t) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()