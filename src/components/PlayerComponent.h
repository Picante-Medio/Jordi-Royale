#pragma once
#include "HugoComponentMacros.h"
#include "HugoTypes.h"

HCOMPONENT(PlayerComponent)
    DEFAULT_SERIALIZED_MEMBER(float, jumpPower, 500.0f);
    DEFAULT_SERIALIZED_MEMBER(float, xpPickupRange, 5.0f);
    DEFAULT_SERIALIZED_MEMBER(float, objectPickupRange, 1.0f);
    DEFAULT_SERIALIZED_MEMBER(HUGO::Int, airJumps, 0);
END_HCOMPONENT()

