#include <exception>

#include "FartonSystem.h"
#include "FartonComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "ColliderComponent.h"

void FartonSystem::init() {
    auto& q = scene.query<PlayerComponent>();
    if(q.size() > 0)
        playerID = q[0].getConst<PlayerComponent>().entity;
    else throw std::runtime_error("Player entity does not exist");
}

void FartonSystem::onLoad() {

}

void FartonSystem::fixedUpdate(uint32_t dt) {
    t += dt;

    // Update existing attack(s)
    for(auto pack : scene.query<FartonComponent, TransformComponent>()) {
        const FartonComponent& farton = pack.getConst<FartonComponent&>();
        const TransformComponent& tr = pack.getConst<TransformComponent&>();

        HUGO::Vector3 dist = tr.rotation.forward() * farton.speed * dt;
        
        pack.modify<TransformComponent>([dist](TransformComponent& tr) {
            tr.position += dist;
        });
        pack.modify<FartonComponent>([dist](FartonComponent& farton) {
            farton.distance += dist.length();
        });
    }

    // Remove overdue attacks
    // Collided with anything
    for(auto pack : scene.query<FartonComponent, ColliderComponent>()) {
        const ColliderComponent& collider = pack.getConst<ColliderComponent&>();
        if(!collider.getCollisionInfo().empty())
            scene.removeEntity(collider.entity);

        // Uncomment to ignore collisions with player
        // std::vector<EntityID> info = collider.getCollisionInfo();
        // if(info.empty()) continue;

        // bool destroy = false;
        // for(auto it = info.begin(); it != info.end() && !destroy; ++it)
        //     destroy = *it != playerID;
        // if(destroy) scene.removeEntity(collider.entity);
    }

    // Exceeded max distance
    for(auto pack : scene.query<FartonComponent>()) {
        const FartonComponent& farton = pack.getConst<FartonComponent&>();
        if(farton.distance > farton.maxDist)
            scene.removeEntity(farton.entity);
    }

    // Instantiate new attack towards closest enemy
    if(t > firingRate) {
        t = 0;
        HUGO::ErrorOrType<EntityID> res = scene.instantiatePrefab(prefab);
        if(!res.isError()) {
            TransformComponent& tr = scene.getComponent<TransformComponent&>(res.getValue());
            
            HUGO::Vector3 target = findClosestEnemy(tr.position);
            tr.rotation = HUGO::lookAt(tr.rotation.forward(), HUGO::Vector3(0,1,0), (target - tr.position)); // no need to normalize

            TransformComponent& playerTr = scene.getComponentConst<TransformComponent&>(playerID);
            tr.position = playerTr.position + instantiateRadius * tr.rotation.forward();
        }
    }

}

void FartonSystem::update(uint32_t) {

}