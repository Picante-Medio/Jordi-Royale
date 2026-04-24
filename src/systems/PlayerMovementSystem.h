#pragma once

#include "HugoSystemMacros.h"
#include "HugoMath.h"

HSYSTEM(PlayerMovementSystem)

HUGO::Vector2 lastMousePosition;
// a value of 1 means that moving the mouse the total horizontal length of the screen will do a 360 degree rotation
HUGO::Float sensibility = 0.5;

public:
void init() override;
void onLoad() override;

void update(uint32_t) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()