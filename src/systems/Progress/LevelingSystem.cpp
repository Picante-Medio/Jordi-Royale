#include "LevelingSystem.h"

#include "EcsTypes.h"
#include "Message.h"
#include "XPComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "LevelComponent.h"
#include "LeveledUpMessage.h"
#include "XPGrabMessage.h"

#include <memory>

void 
LevelingSystem::onLoad(){

}

void 
LevelingSystem::init(){

    // Grab experience through message
    scene.subscribe<XPGrabMessage>([this](std::shared_ptr<HUGO::Message> message){
        std::shared_ptr<XPGrabMessage> m = std::static_pointer_cast<XPGrabMessage>(message);
        EntityID player = scene.query<PlayerComponent>().begin()->getConst<PlayerComponent>().entity;

        scene.modifyComponent<LevelComponent>(player, [m](LevelComponent& lvl){
            lvl.currentExperience += m->xp;
        });
    });
}

void 
LevelingSystem::update(uint32_t){

    // Level up if needed
    for(auto& player : scene.query<PlayerComponent, LevelComponent>()){
        LevelComponent lvlCmp = player.getConst<LevelComponent>();

        // while there's enough experience to level up, the player keeps leveling up
        while(lvlCmp.currentExperience >= lvlCmp.experienceToNextLevel){
            player.modify<LevelComponent>([this](LevelComponent& lvl){
                lvl.currentExperience -= lvl.experienceToNextLevel;
                lvl.level++;
                lvl.experienceToNextLevel += experienceIncrement;
            });

            // We update lvlCmp to get the new values after modify
            lvlCmp = player.getConst<LevelComponent>();

            // We send the level up message
            LeveledUpMessage lvlUp;
            lvlUp.level = lvlCmp.level;
            scene.sendMessage<LeveledUpMessage>(lvlUp);
        }
    }
}

void 
LevelingSystem::fixedUpdate(uint32_t){

}
