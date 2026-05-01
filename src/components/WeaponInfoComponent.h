#pragma once

#include "HUGO.h"
#include "HugoComponentMacros.h"

HCOMPONENT(WeaponInfoComponent)

enum WeaponType {
    Melee,
    Ranged,
    Area
};

HUGO::String prefab;

// ms between firing each attack
int32_t firingRate;

// direction in which a projectile is fired
// can be costant or variable
std::function<HUGO::Quaternion(uint32_t)> initialDirection;

WeaponType type;

END_HCOMPONENT()
