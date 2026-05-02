#pragma once

#include "HUGO.h"
#include "ProjectileComponent.h"

HSYSTEM(ProjectileSystem)

public:
    void init() override;
    void onLoad() override;

    void fixedUpdate(uint32_t dt) override;
    void update(uint32_t dt) override;

private:
    // returns delta position (m). Parameters: s (speed magnitude)
    static float mru(float s, uint32_t t);
    // returns delta position (m). Parameters: s0 (initial speed), a (acceleration magnitude)
    static float mrua(float s0, float a, uint32_t t);
    // returns delta position (m). Parameters: A (amplitude), b (shift left/right), c (shift up/down), k (period)
    static float sin(float A, float b, float c, float k, uint32_t t);

    static std::pair<int, float> getDeltaPosition(const ProjectilePath& path, uint32_t dt);

END_HSYSTEM()