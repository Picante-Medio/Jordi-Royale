#pragma once

#include "HUGO.h"

HCOMPONENT(ProjectileComponent)

SERIALIZED_MEMBER(HUGO::Int, lifetime); // m/s

SERIALIZED_MEMBER(HUGO::Float, speed); // m/s
uint32_t t = 0; // ms, time it's been alive for

/// @brief lambda function that describes the direction of the projectile, based on its speed and delta time
/// @param projectileComp <ProjectileComponent> this component, so it can access t and speed members
std::function<HUGO::Vector3(ProjectileComponent)> nextDirection;

END_HCOMPONENT()