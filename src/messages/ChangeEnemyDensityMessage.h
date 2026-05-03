#pragma once
#include "Message.h"
#include <cstdint>

struct ChangeEnemyDensityMessage : public HUGO::Message {

    uint32_t milisecondsBetweenSpawns = 1500;
};
