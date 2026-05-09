#pragma once

#include "HUGO.h"

struct HealPlayerMessage : public HUGO::Message {
    HUGO::Int healPoints;
};
