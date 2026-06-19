#pragma once
#include "EcsTypes.h"
#include "Message.h"

struct PlayerDeadMessage : public HUGO::Message {
    EntityID player;
};
