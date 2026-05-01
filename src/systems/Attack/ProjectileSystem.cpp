#include <cmath>

#include "ProjectileSystem.h"
#include "ProjectileComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "DestroyOnEnemyContactTag.h"
#include "DestroyOnPlayerContactTag.h"
#include "PlayerTag.h"
#include "EnemyTag.h"

void ProjectileSystem::init() {

}

void ProjectileSystem::onLoad() {

}

void ProjectileSystem::fixedUpdate(uint32_t dt) {
    // update position of every projectile
    for(auto pack : scene.query<ProjectileComponent, RigidBodyComponent, TransformComponent>()) {
        pack.modify<ProjectileComponent>([dt] (ProjectileComponent& comp) {
            comp.lifetime -= dt;

            std::get_if<MRU>(&comp.pathX);
        });

        // if(pack.getConst<RigidBodyComponent>().getBodyType() == HUGO::BodyType::KINEMATIC) {

        //     const ProjectileComponent& projectileComp = pack.getConst<ProjectileComponent>() ;
        //     pack.modify<TransformComponent>([projectileComp, dt] (TransformComponent&tr){

        //         HUGO::Vector3 dir = projectileComp.nextDirection(projectileComp, speed);
        //         tr.setPosition(tr.getPosition() + dir*dt);
        //     });
        // }

        // calculate position
        const ProjectileComponent& projectileComp = pack.getConst<ProjectileComponent>();
        const TransformComponent& transform = pack.getConst<TransformComponent>();

        
        // apply position to transform
    }
}

void ProjectileSystem::update(uint32_t) {
    // check for projectiles that must be destroyed
    for(auto pack : scene.query<ProjectileComponent, ColliderComponent>()) {

        const ProjectileComponent& projectileComp = pack.getConst<ProjectileComponent>();
        if(projectileComp.lifetime <= 0) {
            scene.removeEntity(projectileComp.entity);
            continue;
        }

        const ColliderComponent& collider = pack.getConst<ColliderComponent>();
        if(collider.collisionInfo.empty())
            continue;

        bool destroyOnEnemyContact = scene.hasComponent<DestroyOnEnemyContactTag>(collider.entity);
        bool destroyOnPlayerContact = scene.hasComponent<DestroyOnPlayerContactTag>(collider.entity);

        if (!destroyOnEnemyContact && !destroyOnPlayerContact) 
            return;

        for(EntityID id : collider.collisionInfo) {
            if(destroyOnEnemyContact && scene.hasComponent<EnemyTag>(id)) {
                scene.removeEntity(collider.entity);
                break;
            }

            if(destroyOnPlayerContact && scene.hasComponent<PlayerTag>(id)) {
                scene.removeEntity(collider.entity);
                break;
            }
        }
    }
}

float ProjectileSystem::mru(float x0, float s, uint32_t t) {
    return x0 + s*t;
}

float ProjectileSystem::mrua(float x0, float s0, float a, uint32_t t) {
    return x0 + s0*t + 0.5f*a*t*t;
}

// float ProjectileSystem::mcu(float rad0, float w, float R, uint32_t t) {
//     return (rad0 + w*t) * R;
// }

float ProjectileSystem::sin(float A, float b, float c, float k, uint32_t t) {
    return A * std::sin(k*(t-b)) + c;
}