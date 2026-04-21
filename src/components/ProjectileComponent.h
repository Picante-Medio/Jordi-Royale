#pragma once

#include "HugoComponentMacros.h"

HCOMPONENT(ProjectileComponent)

HUGO::Int lifetime; // ms

HUGO::Float speed; // m/s
uint32_t t;

/// @brief lambda function that describes the direction of the projectile, based on its speed and delta time
/// @param t <uint32_t> time since spawn in ms
/// @param speed <HUGO::Float> speed in m/s
std::function<HUGO::Vector3(uint32_t, HUGO::Float)> nextDirection;

END_HCOMPONENT()