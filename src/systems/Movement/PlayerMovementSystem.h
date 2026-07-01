#pragma once

#include "HugoSystemMacros.h"
#include "HugoMath.h"

struct TransformComponent;
HSYSTEM(PlayerMovementSystem)

const float SENSIBILITY = 0.001;

// vector from camera to Jordi in x and z exes
HUGO::Vector3 diffVectorxz;

float yOffset = 3;

void updateCameraPivot();

public:
void init() override;
void onLoad() override;

void update(uint32_t) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()
