#include "RotateSystem.h"
#include "RotateComponent.h"
#include "TransformComponent.h"

void RotateSystem::update(uint32_t dt) {
    for(auto pack: scene.query<TransformComponent, RotateComponent>()){
        auto s = pack.getConst<RotateComponent>().speed;
        pack.modify<TransformComponent>([dt, s](TransformComponent& tr){
            HUGO::Quaternion addedRot = HUGO::Quaternion(HUGO::Degree(s * dt/1000.), HUGO::Vector3(0,1,0));
            tr.rotation *= addedRot;
        });
    }
}
