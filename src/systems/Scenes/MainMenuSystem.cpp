#include "MainMenuSystem.h"
#include "EcsTypes.h"
#include "PlayerComponent.h"
#include "AnimationComponent.h"

void 
MainMenuSystem::onLoad() {
    for(auto jordi : scene.query<AnimationComponent>()) {
        jordi.modify<AnimationComponent>([](AnimationComponent& ac){
            ac.addAnimation("Idle", true);
            ac.setEnabled("Idle", true);
        });
    }
}
