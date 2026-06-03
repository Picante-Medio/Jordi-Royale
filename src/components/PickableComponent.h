#pragma once

#include "HugoComponentMacros.h"
#include "HugoTypes.h"

HCOMPONENT(PickableComponent)
    DEFAULT_SERIALIZED_MEMBER(float, pickupRadius, 0.5f);
END_HCOMPONENT()
