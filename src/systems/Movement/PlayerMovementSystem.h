#pragma once

#include "HugoSystemMacros.h"
#include "HugoMath.h"

struct TransformComponent;
HSYSTEM(PlayerMovementSystem)

HUGO::Vector2 lastMousePosition;
// a value of 1 means that moving the mouse the total horizontal length of the screen will do a 360 degree rotation
const HUGO::Float SENSIBILITY = 0.75;

// vector from camera to Jordi in x and z exes
HUGO::Vector3 diffVectorxz;

HUGO::Float yOffset = 1.4;

void updateCamera(TransformComponent& playerTrans);

public:
void init() override;
void onLoad() override;

void update(uint32_t) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()
