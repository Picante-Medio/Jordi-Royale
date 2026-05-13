#pragma once
#include "EcsTypes.h"
#include "HugoSystemMacros.h"

HSYSTEM(DamageSystem)
private:
void changeHP(EntityID id, HUGO::Int hp);
EntityID playerID;

float msCooldown = 300;
float timeSinceCooldown = 300;

public:
void init() override;
void onLoad() override;

void update(uint32_t dt) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()