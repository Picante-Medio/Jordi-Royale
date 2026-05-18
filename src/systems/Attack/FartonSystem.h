#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(FartonSystem)

public:
    void init() override;
    void onLoad() override;

    void fixedUpdate(uint32_t dt) override;
    void update(uint32_t dt) override;

private:
    EntityID playerID;

    uint32_t t = 0;
    uint32_t firingRate = 400;

    float instantiateRadius = 1.f;

    std::string prefab = "Farton";

    std::set<EntityID> toRemove;

    HUGO::Vector3 findClosestEnemy(HUGO::Vector3 pos);
END_HSYSTEM()
