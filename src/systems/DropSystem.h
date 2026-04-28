#pragma once

#include "EcsTypes.h"
#include "HugoMath.h"
#include "HUGO.h"

const int HP_FOR_SPAWN = 50;

HSYSTEM(DropSystem)
    void killEnemy(EntityID enemy);
    void spawnChest(HUGO::Vector3 position);
    void spawnXP(HUGO::Vector3 position, int amount);
public:
    void init() override;
    void onLoad() override {};
    void update(uint32_t dt) override; 

    inline void fixedUpdate(uint32_t) override {};
END_HSYSTEM()
