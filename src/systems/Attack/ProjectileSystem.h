#pragma once

#include "HUGO.h"

HSYSTEM(ProjectileSystem)

public:
    void init() override;
    void onLoad() override;

    void fixedUpdate(uint32_t dt) override;
    void update(uint32_t dt) override;

private:
    // returns position (m). Parameters: x0 (initial position), s (speed magnitude)
    float mru(float x0, float s, uint32_t t);
    // returns position (m). Parameters: x0 (initial position), s0 (initial speed), a (acceleration magnitude)
    float mrua(float x0, float s0, float a, uint32_t t);
    // returns position (m). Parameters: rad0 (initial angle in radians), w (angular speed), R (radius)
    // float mcu(float rad0, float w, float R, uint32_t t);
    // returns position (m). Parameters: A (amplitude), b (shift left/right), c (shift up/down), k (period)
    float sin(float A, float b, float c, float k, uint32_t t);

    

END_HSYSTEM()