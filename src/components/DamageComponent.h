#pragma once

#include "HugoComponentMacros.h"

HCOMPONENT(DamageComponent)
enum DamageType{
    Enemy,
    Player
};

HUGO::Int Damage = 10;
DamageType DamType = Player;

END_HCOMPONENT()