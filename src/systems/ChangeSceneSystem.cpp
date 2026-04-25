#include "ChangeSceneSystem.h"

#include <memory>

#include "ChangeSceneMessage.h"
#include "HugoInputCodes.h"

void 
ChangeSceneSystem::init() {
    // scene.subscribe<ChangeSceneMessage>([this](std::shared_ptr<HUGO::Message> message) {
    //     std::shared_ptr<ChangeSceneMessage> m = std::static_pointer_cast<ChangeSceneMessage>(message);
    //     if(m->destroyCurrent) scene.changeAndDestroyPreviousScene(m->sceneName);
    //     else scene.changeScene(m->sceneName);
    // });
}

void 
ChangeSceneSystem::update(uint32_t) {
    // if(scene.getInput()->isKeyPressed(HUGO::KeyCode::ESC)) {
    //     ChangeSceneMessage message;
    //     message.sceneName = "PauseScene";
    //     message.destroyCurrent = false;

    //     scene.sendMessage<ChangeSceneMessage>(message);
    // }
}

void
ChangeSceneSystem::fixedUpdate(uint32_t){

}