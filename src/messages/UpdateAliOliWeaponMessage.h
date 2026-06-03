#pragma once
#include "HUGO.h"

struct UpdateAliOliWeaponMessage : public HUGO::Message{

    float damageToAdd = 0;
    HUGO::Int countToAdd = 0;
};