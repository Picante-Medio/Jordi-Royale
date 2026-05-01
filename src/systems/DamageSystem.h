#pragma once
#include "Message.h"
#include "HugoSystemMacros.h"

HSYSTEM(DamageSystem)
private:
EntityID playerID;
void changeHP(EntityID id, HUGO::Int hp);

public:
void init() override;
void onLoad() override;

void update(uint32_t) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()
