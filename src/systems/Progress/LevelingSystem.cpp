#include "LevelingSystem.h"

#include "XPComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "LevelComponent.h"

#include "LeveledUpMessage.h"

void 
LevelingSystem::onLoad(){

}

void 
LevelingSystem::init(){

}

void 
LevelingSystem::update(uint32_t){

    // Grab experience
    for(auto& xp : scene.query<XPComponent, TransformComponent>()){
        for(auto& player : scene.query<PlayerComponent, TransformComponent, LevelComponent>()){
            TransformComponent xpTrans = xp.getConst<TransformComponent>();
            TransformComponent playerTrans = player.getConst<TransformComponent>();

            HUGO::Vector3 distance = xpTrans.getPosition() - playerTrans.getPosition();
            float distanceModule = distance.length();

            if(distanceModule < grabDistance){
                player.modify<LevelComponent>([xp](LevelComponent& lvl){

                    lvl.currentExperience += xp.getConst<XPComponent>().experience;
                });

                // Animation of experience moving towards player may be added (optional)
                scene.removeEntity(xpTrans.entity);
            }
        }
    }

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
