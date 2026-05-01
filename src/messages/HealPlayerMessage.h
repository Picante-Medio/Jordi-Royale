#pragma once

#include "EcsTypes.h"
#include "Message.h"
#include "HugoTypes.h"

struct HealPlayerMessage : public HUGO::Message {
    HUGO::Int healPoints;
};