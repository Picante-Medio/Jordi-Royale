#pragma once 

#include <string>
#include "Message.h"

struct ChangeToNewInstanceOfSceneMessage: public HUGO::Message {
    std::string sceneName = "main_scene";
    bool destroyCurrent = true;
};
