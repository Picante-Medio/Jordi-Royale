#include <cmath>

#include "ProjectileSystem.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "DestroyOnEnemyContactTag.h"
#include "DestroyOnPlayerContactTag.h"
#include "PlayerComponent.h"
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
        });

        const ProjectileComponent& projectileComp = pack.getConst<ProjectileComponent>();
        const TransformComponent& transform = pack.getConst<TransformComponent>();

        // Right delta position
        std::pair<int,float> dx = getDeltaPosition(projectileComp.pathX, dt);
        if(dx.first == ProjectileComponent::PathType::mrua) {         
            // update speed accordingly
            pack.modify<ProjectileComponent>([dt] (ProjectileComponent& comp) {
                MRUA m = std::get<MRUA>(comp.pathX);
                m.s += m.a * dt;
            });
        }

        HUGO::Vector3 deltaRight = transform.getRotation().right() * dx.second;
        
        // Up delta position
        std::pair<int,float> dy = getDeltaPosition(projectileComp.pathY, dt);
        if(dy.first == ProjectileComponent::PathType::mrua) {         
            // update speed accordingly
            pack.modify<ProjectileComponent>([dt] (ProjectileComponent& comp) {
                MRUA m = std::get<MRUA>(comp.pathY);
                m.s += m.a * dt;
            });
        }
        
        HUGO::Vector3 deltaUp = transform.getRotation().up() * dy.second;
        
        // Forward delta position
        std::pair<int,float> dz = getDeltaPosition(projectileComp.pathZ, dt);
        if(dz.first == ProjectileComponent::PathType::mrua) {         
            // update speed accordingly
            pack.modify<ProjectileComponent>([dt] (ProjectileComponent& comp) {
                MRUA m = std::get<MRUA>(comp.pathZ);
                m.s += m.a * dt;
            });
        }
        
        HUGO::Vector3 deltaForward = transform.getRotation().forward() * dz.second;
              
        // Apply position to transform
        HUGO::Vector3 deltaPosition = deltaRight + deltaUp + deltaForward;
        pack.modify<TransformComponent>([deltaPosition](TransformComponent& tr) {
            tr.setWorldPosition(tr.getWorldPosition() + deltaPosition);
        });
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

            if(destroyOnPlayerContact && scene.hasComponent<PlayerComponent>(id)) {
                scene.removeEntity(collider.entity);
                break;
            }
        }
    }
}

float ProjectileSystem::mru(float s, uint32_t t) {
    return s*t;
}

float ProjectileSystem::mrua(float s0, float a, uint32_t t) {
    return s0*t + 0.5f*a*t*t;
}

float ProjectileSystem::sin(float A, float b, float c, float k, uint32_t t) {
    return A * std::sin(k*(t-b)) + c;
}

std::pair<int, float> ProjectileSystem::getDeltaPosition(const ProjectilePath& path, uint32_t dt) {
    std::pair<int,float> dx{0, 0.f};

    if(std::holds_alternative<MRU>(path)) {
        const MRU& movement = std::get<MRU>(path);
        dx.first = ProjectileComponent::PathType::mru;
        dx.second = mru(movement.s, dt);
    }
    else if(std::holds_alternative<MRUA>(path)) {
        const MRUA& movement = std::get<MRUA>(path);
        dx.first = ProjectileComponent::PathType::mrua;
        dx.second = mrua(movement.s, movement.a, dt);
    }
    else if(std::holds_alternative<SIN>(path)) {
        const SIN& movement = std::get<SIN>(path);
        dx.first = ProjectileComponent::PathType::sin;
        dx.second = sin(movement.A, movement.b, movement.c, movement.k, dt);
    }

    return dx;
}