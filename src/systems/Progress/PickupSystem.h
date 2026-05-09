# pragma once

#include <cstdint>

#include "HugoSystemMacros.h"
#include "TransformComponent.h"

HSYSTEM(PickupSystem)
    bool pickup(const TransformComponent& playerTransform, const TransformComponent& pickupTransform, float pickupRange);
public:
    void update(uint32_t dt) override;

    void init() override {}
    void onLoad() override {}
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()
