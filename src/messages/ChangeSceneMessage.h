#pragma once

#include <string>
#include "Message.h"

struct ChangeSceneMessage : public HUGO::Message {
    std::string sceneName = "main_scene";
    bool destroyCurrent = true;
};
