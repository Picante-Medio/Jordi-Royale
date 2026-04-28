#pragma once

#include "HUGO.h"

HCOMPONENT(WeaponInfoComponent)

enum WeaponType {
    Melee,
    Ranged,
    Area
};

HUGO::String prefab;

// ms between firing an attack
int32_t firingRate;

std::function<HUGO::Quaternion(uint32_t)> initialDirection;

WeaponType type;

HCOMPONENT_END()