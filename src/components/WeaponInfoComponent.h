#pragma once

#include "HUGO.h"
#include "HugoComponentMacros.h"

HCOMPONENT(WeaponInfoComponent)

HUGO::String prefab;

// ms between firing each attack
uint32_t firingRate;
uint32_t t;

// direction in which a projectile is fired
// can be costant or variable
std::function<HUGO::Quaternion(uint32_t)> initialDirection;

END_HCOMPONENT()
