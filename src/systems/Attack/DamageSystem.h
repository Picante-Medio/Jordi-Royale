#pragma once
#include "EcsTypes.h"
#include "HugoSystemMacros.h"

HSYSTEM(DamageSystem)
private:
void changeHP(EntityID id, HUGO::Int hp);
EntityID playerID;

HUGO::Float msEnemyCooldown = 300;
HUGO::Float timeSinceEnemyCooldown = 300;

HUGO::Float msPlayerCooldown = 300;
HUGO::Float timeSincePlayerCooldown = 300;

public:
void init() override;
void onLoad() override;

void update(uint32_t dt) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()