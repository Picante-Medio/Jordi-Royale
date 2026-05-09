#pragma once

#include "HUGO.h"

HCOMPONENT(DamageComponent)

enum DamageType{
    Enemy,
    Player
};

DEFAULT_SERIALIZED_MEMBER(HUGO::Int, Damage, 10);
DamageType DamType = Player;

END_HCOMPONENT()