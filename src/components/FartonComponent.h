#pragma once

#include "HugoComponentMacros.h"

HCOMPONENT(FartonComponent)

DEFAULT_SERIALIZED_MEMBER(float, maxDist, 10.0f)

DEFAULT_SERIALIZED_MEMBER(float, speed, 3.0f)

float distance = 0.0f;

END_HCOMPONENT()
