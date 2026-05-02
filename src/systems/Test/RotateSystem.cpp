#include "RotateSystem.h"
#include "RotateComponent.h"
#include "TransformComponent.h"

void RotateSystem::update(uint32_t dt) {
    for(auto pack: scene.query<TransformComponent, RotateComponent>()){
        pack.modify<TransformComponent>([dt](TransformComponent& tr){
            auto currRot = tr.getRotation();
            HUGO::Quaternion addedRot = HUGO::Quaternion(HUGO::Degree(20 * dt/1000.), HUGO::Vector3(0,1,0));

            tr.setRotation(currRot * addedRot);
        });
    }
}