#pragma once

#include "EcsTypes.h"
#include "Message.h"

struct EnemyDeadMessage : public HUGO::Message {
    EntityID enemy;
};
