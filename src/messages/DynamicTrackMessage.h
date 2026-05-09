#pragma once

#include "HUGO.h"

enum Action {
    TOGGLE,
    ACTIVATE,
    DEACTIVATE,
};

struct DynamicTrackMessage : HUGO::Message {

    HUGO::String trackName = "";
    Action action;
};
