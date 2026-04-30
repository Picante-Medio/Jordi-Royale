#pragma once
#include "Message.h"
#include "HugoSystemMacros.h"

HSYSTEM(DamageSystem)
private:
EntityID playerID;
void heal(std::shared_ptr<HUGO::Message> m);

public:
void init() override;
void onLoad() override;

void update(uint32_t) override;
void fixedUpdate(uint32_t) override;

END_HSYSTEM()
