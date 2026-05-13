#include "EnemyMovementSystem.h"

#include <math.h>

#include "EcsTypes.h"
#include "EnemyTag.h"
#include "HugoMath.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"
#include "SpeedComponent.h"
#include "TransformComponent.h"

void 
EnemyMovementSystem::init() {
}

void 
EnemyMovementSystem::onLoad() {}

void 
EnemyMovementSystem::fixedUpdate(uint32_t dt) {

    EntityID jordi = scene.query<PlayerComponent>().begin()->getConst<PlayerComponent>().entity;

    // Move enemies towards Jordi
    for(auto pack : scene.query<EnemyTag, RigidBodyComponent, TransformComponent, SpeedComponent>()) {
        pack.modify<RigidBodyComponent>([this, dt, jordi, &pack](RigidBodyComponent& rb) {
            const HUGO::Vector3 direction = scene.getComponentConst<TransformComponent>(jordi).position - pack.getConst<TransformComponent>().position;
            const HUGO::Vector3 desiredVel = direction.normalized() * pack.getConst<SpeedComponent>().speed;
            const HUGO::Vector3 velError = desiredVel - rb.getLinearVelocity();
            const float dtSeconds = dt / 1000.0f;

            rb.applyForce(rb.mass * velError / dtSeconds);

            pack.modify<TransformComponent>([rb, &direction](TransformComponent& trans){
                    if(direction == HUGO::Vector3()) return;
                    HUGO::Vector3 rotDirection = HUGO::Vector3(direction.x, 0, direction.z);
                    HUGO::Vector3 rotation = HUGO::Vector3(0, 0, 1).cross(rotDirection);
                    HUGO::Float wValue = sqrt(pow(HUGO::Vector3(0, 0, 1).length(), 2) * pow(rotDirection.length(), 2)) + rotDirection.z;
                    trans.rotation = (HUGO::Quaternion(wValue, rotation.x, rotation.y, rotation.z) * HUGO::Quaternion(HUGO::Degree(270), HUGO::Vector3(0,1,0)));
    
                    // Needed because previous calculations doesn't work properly when going forward and I don't know math
                    if(trans.rotation == HUGO::Quaternion(0, 0, 0, 0))
                        trans.rotation = (HUGO::Quaternion(HUGO::Degree(180), HUGO::Vector3(0, 1, 0)) * HUGO::Quaternion(HUGO::Degree(270), HUGO::Vector3(0,1,0)));
                });

        });
    }
}
