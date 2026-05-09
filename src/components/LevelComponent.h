#pragma once

#include "HUGO.h"

HCOMPONENT(LevelComponent)

DEFAULT_SERIALIZED_MEMBER(int, level, 1)

// Provisional values. Test is needed
unsigned long int currentExperience = 0;
unsigned long int experienceToNextLevel = 100;

END_HCOMPONENT()