#include "EnemyMovementSystem.h"

#include "EnemyComponent.h"
#include "HugoMath.h"
#include "RigidBodyComponent.h"
#include "PlayerTag.h"
#include "SpeedComponent.h"
#include "TransformComponent.h"

void 
EnemyMovementSystem::init() {
    // Find jordi
    for(auto pack : scene.query<PlayerTag>())
        jordi = pack.getConst<PlayerTag>().entity;
}

void 
EnemyMovementSystem::onLoad() {

}

void 
EnemyMovementSystem::fixedUpdate(uint32_t dt) {

    for(auto pack : scene.query<EnemyComponent, RigidBodyComponent, TransformComponent, SpeedComponent>()) {
        pack.modify<RigidBodyComponent>([this, dt](RigidBodyComponent& rb, TransformComponent& tr, SpeedComponent& speed) {
            const HUGO::Vector3 direction = scene.getComponentConst<TransformComponent>(jordi).getPosition() - tr.getPosition();
            const HUGO::Vector3 desiredVel = direction * speed.speed;
            const HUGO::Vector3 velError = desiredVel - rb.getLinearVelocity();

            rb.applyForce(rb.mass * velError / dt); // I think this is the formula
        });
    }
}
