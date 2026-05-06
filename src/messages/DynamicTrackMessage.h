#pragma once

#include "HugoTypes.h"
#include "Message.h"

enum Action {
    TOGGLE,
    ACTIVATE,
    DEACTIVATE,
};

struct DynamicTrackMessage : HUGO::Message {

    HUGO::String trackName = "";
    Action action;
};
