#pragma once

#include "HugoComponentMacros.h"

HCOMPONENT(HPComponent)

DEFAULT_SERIALIZED_MEMBER(HUGO::Int, HPMax, 100);
DEFAULT_SERIALIZED_MEMBER(HUGO::Int, CurrentHP, 100);

bool dead = false;

END_HCOMPONENT()
