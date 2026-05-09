#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(RotateSystem)
public:
void init() override{};
void onLoad() override{};

void update(uint32_t) override;
void fixedUpdate(uint32_t) override{};

END_HSYSTEM()
