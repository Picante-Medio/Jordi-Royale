#pragma once
#include "HugoComponentMacros.h"
#include "HugoTypes.h"

HCOMPONENT(PlayerComponent)
    DEFAULT_SERIALIZED_MEMBER(HUGO::Float, jumpPower, 500.0f);
    DEFAULT_SERIALIZED_MEMBER(HUGO::Float, pickupRange, 5.0f);
    DEFAULT_SERIALIZED_MEMBER(HUGO::Int, airJumps, 0);

END_HCOMPONENT()

