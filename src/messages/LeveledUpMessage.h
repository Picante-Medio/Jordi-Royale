#pragma once
#include "Message.h"

struct LeveledUpMessage : public HUGO::Message {
    unsigned int level;
};
