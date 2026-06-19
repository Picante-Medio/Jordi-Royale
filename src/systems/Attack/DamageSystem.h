#pragma once
#include "EcsTypes.h"
#include "HugoSystemMacros.h"

HSYSTEM(DamageSystem)
private:
void changeHP(EntityID id, HUGO::Int hp);
EntityID playerID;

float msEnemyCooldown = 300;
float timeSinceEnemyCooldown = 300;

float msPlayerCooldown = 300;
float timeSincePlayerCooldown = 300;

public:
void init() override;
void onLoad() override;

void update(uint32_t dt) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()