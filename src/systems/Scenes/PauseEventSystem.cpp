#include "PauseEventSystem.h"
#include <cstdint>

#include "ChangeSceneMessage.h"

void 
PauseEventSystem::update(uint32_t dt) {
    if(scene.getInput().isKeyPressed(HUGO::KeyCode::ESC)) {
        ChangeSceneMessage message;
        message.sceneName = "pause_scene";
        message.destroyCurrent = false;

        scene.sendMessage<ChangeSceneMessage>(message);
    }
}
