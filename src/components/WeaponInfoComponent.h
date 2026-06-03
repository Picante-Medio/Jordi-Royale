#pragma once

#include "HugoComponentMacros.h"

HCOMPONENT(WeaponInfoComponent)

std::string prefab;

// ms between firing each attack
uint32_t firingRate;
uint32_t t;

// direction in which a projectile is fired
// can be costant or variable
std::function<HUGO::Vector3(uint32_t)> initialDirection;

END_HCOMPONENT()
