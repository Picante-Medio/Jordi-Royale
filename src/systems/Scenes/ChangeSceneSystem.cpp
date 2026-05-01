#include "ChangeSceneSystem.h"

#include <memory>

#include "ChangeSceneMessage.h"
#include "PlayerDeadMessage.h"
#include "HugoInputCodes.h"

void 
ChangeSceneSystem::init() {
    // Callback to process scene change requests
    scene.subscribe<ChangeSceneMessage>([this](std::shared_ptr<HUGO::Message> message) {
        std::shared_ptr<ChangeSceneMessage> m = std::static_pointer_cast<ChangeSceneMessage>(message);
        if(m->destroyCurrent) scene.changeAndDestroyPreviousScene(m->sceneName);
        else scene.changeScene(m->sceneName);
    });

    // If player dies, change scene to losing
    scene.subscribe<PlayerDeadMessage>([this](std::shared_ptr<HUGO::Message> message){
        ChangeSceneMessage signal;
        signal.sceneName = "lose_scene";
        signal.destroyCurrent = true;

        scene.sendMessage(signal);
    });
}

void
ChangeSceneSystem::update(uint32_t) {
    // Pause handling
    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::ESC)) {
        ChangeSceneMessage message;
        message.sceneName = "pause_scene";
        message.destroyCurrent = false;

        scene.sendMessage<ChangeSceneMessage>(message);
    }
}
