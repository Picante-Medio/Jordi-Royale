#pragma once
#include "EcsTypes.h"
#include "HugoSystemMacros.h"

HSYSTEM(DamageSystem)
private:
void changeHP(EntityID id, HUGO::Int hp);
EntityID playerID;
public:
void init() override;
void onLoad() override;

void update(uint32_t) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()