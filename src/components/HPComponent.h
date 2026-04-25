#pragma once

#include "HugoComponentMacros.h"

HCOMPONENT(HPComponent)

DEFAULT_SERIALIZED_MEMBER(int, HPMax, 100);
DEFAULT_SERIALIZED_MEMBER(int, CurrentHP, 100);

END_HCOMPONENT()
