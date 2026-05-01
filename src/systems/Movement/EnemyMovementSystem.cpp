#include "EnemyMovementSystem.h"

#include "EcsTypes.h"
#include "EnemyComponent.h"
#include "HugoMath.h"
#include "RigidBodyComponent.h"
#include "PlayerTag.h"
#include "SpeedComponent.h"
#include "TransformComponent.h"

void 
EnemyMovementSystem::init() {}

void 
EnemyMovementSystem::onLoad() {}

void 
EnemyMovementSystem::fixedUpdate(uint32_t dt) {
    // Find Jordi
    EntityID jordi = scene.query<PlayerTag>().begin()->getConst<PlayerTag>().entity;

    // Move enemies towards Jordi
    for(auto pack : scene.query<EnemyComponent, RigidBodyComponent, TransformComponent, SpeedComponent>()) {
        pack.modify<RigidBodyComponent>([this, jordi, dt, pack](RigidBodyComponent& rb) {
            const HUGO::Vector3 direction = scene.getComponentConst<TransformComponent>(jordi).getPosition() - pack.getConst<TransformComponent>().getPosition();
            const HUGO::Vector3 desiredVel = direction * pack.getConst<SpeedComponent>().speed;
            const HUGO::Vector3 velError = desiredVel - rb.getLinearVelocity();

            rb.applyForce(rb.mass * velError / dt); // I think this is the formula
        });
    }
}
