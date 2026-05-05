#include "EnemyAnimationSystem.h"
#include "EnemyTag.h"

void EnemyAnimationSystem::init(){

}

void EnemyAnimationSystem::setIdle(AnimationComponent& cmp){
    if(scene.hasComponent<EnemyTag>(cmp.entity)){
        cmp.addAnimation("Idle", true);
        cmp.setLoop("Idle", true);
        cmp.setEnabled("Idle", true);
        scene.log("Animation added");
    }
}

void EnemyAnimationSystem::update(uint32_t){
    for(auto pack: scene.query<EnemyTag, AnimationComponent>()){
        pack.modify<AnimationComponent>([](AnimationComponent& cmp){
            if(!cmp.anims.count("Idle")){
                cmp.addAnimation("Idle");
                cmp.setEnabled("Idle", true);
                cmp.setLoop("Idle", true);
                
            }
        });
    }
}