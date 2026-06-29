#include "ChangeSceneSystem.h"

#include <iostream>
#include <memory>

#include "ChangeSceneMessage.h"
#include "Message.h"
#include "PlayerDeadMessage.h"
#include "LeveledUpMessage.h"
#include "ChestGrabMessage.h"

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
        scene.changeAndDestroyPreviousScene("lose_scene");
    });
    
    scene.subscribe<LeveledUpMessage>([this](std::shared_ptr<HUGO::Message> message) {
        scene.changeScene("upgrades_scene");
    });
    
    scene.subscribe<ChestGrabMessage>([this](std::shared_ptr<HUGO::Message> message) {
        scene.changeScene("upgrades_scene");
    });

}

void
ChangeSceneSystem::update(uint32_t) {}
