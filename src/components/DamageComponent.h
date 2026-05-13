#pragma once

#include "HugoComponentMacros.h"

HCOMPONENT(DamageComponent)

enum DamageType{
    Enemy,
    Player
};

DEFAULT_SERIALIZED_MEMBER(HUGO::Int, Damage, 10);
DEFAULT_SERIALIZED_MEMBER(HUGO::Int, DamType, 1);

END_HCOMPONENT()