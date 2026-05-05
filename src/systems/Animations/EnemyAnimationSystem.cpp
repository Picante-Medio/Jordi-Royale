#include "EnemyAnimationSystem.h"
#include "EnemyTag.h"

void EnemyAnimationSystem::init(){
    scene.onAddComponent<AnimationComponent>().connect(this, &EnemyAnimationSystem::setIdle);
}

void EnemyAnimationSystem::setIdle(AnimationComponent& cmp){
    if(scene.hasComponent<EnemyTag>(cmp.entity)){
        cmp.addAnimation("Idle", true);
        cmp.setEnabled("Idle", true);
        scene.log("Animation added");
    }
}