#pragma once
#include "HUGO.h"

struct UpdateAliOliWeaponMessage : public HUGO::Message{

    HUGO::Float damageToAdd = 0;
    HUGO::Int countToAdd = 0;
};