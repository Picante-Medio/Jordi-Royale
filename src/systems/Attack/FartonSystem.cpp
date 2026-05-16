#include <cfloat>
#include <exception>
#include <limits>
#include <set>

#include "FartonSystem.h"
#include "FartonComponent.h"
#include "TransformComponent.h"
#include "WorldTransformComponent.h"
#include "PlayerComponent.h"
#include "ColliderComponent.h"
#include "EnemyTag.h"
#include "RigidBodyComponent.h"

void FartonSystem::init() {
    toRemove = std::set<EntityID>();
}

void FartonSystem::onLoad() {
    auto q = scene.query<PlayerComponent>();
    if(q.size() > 0)
        playerID = q[0].getConst<PlayerComponent>().entity;
    else throw std::runtime_error("Player entity does not exist");
}

void FartonSystem::fixedUpdate(uint32_t dt) {
    t += dt;

    // Update existing attack(s)
    for(auto pack : scene.query<FartonComponent, RigidBodyComponent, WorldTransformComponent>()) {
        const FartonComponent& farton = pack.getConst<FartonComponent>();
        const RigidBodyComponent& rb = pack.getConst<RigidBodyComponent>();
        const WorldTransformComponent& tr = pack.getConst<WorldTransformComponent>();

        pack.modify<RigidBodyComponent>([farton, tr](RigidBodyComponent& rb) {
            rb.setLinearVelocity(farton.speed * tr.worldRotation.forward());
        });

        // std::cout << "Farton " << tr.entity << " forward: " << tr.worldRotation.forward().x << " " << tr.worldRotation.forward().y << " " << tr.worldRotation.forward().z << "\n";
        HUGO::Vector3 dist = tr.worldRotation.forward() * farton.speed * dt * 0.001f;
        
        pack.modify<FartonComponent>([dist](FartonComponent& farton) {
            farton.distance += dist.length();
            // std::cout << "Distancia recorrida del farton " << farton.entity << " : " << farton.distance << "\n";
        });
    }


    // Remove overdue attacks
    for(auto pack : scene.query<FartonComponent, ColliderComponent>()) {
        // Collided with anything
        const ColliderComponent collider = pack.getConst<ColliderComponent>();
        // if(!collider.getCollisionInfo().empty())
        //     toRemove.insert(collider.entity);

        // Ignore collisions with player
        // std::vector<EntityID> info = collider.getCollisionInfo();
        // if(!info.empty()) {   
        //     bool destroy = false;
        //     for(auto it = info.begin(); it != info.end() && !destroy; ++it)
        //     destroy = *it != playerID;
        //     if(destroy) toRemove.insert(collider.entity);
        // }

        // // Exceeded max distance
        // const FartonComponent farton = pack.getConst<FartonComponent>();
        // if(farton.distance > farton.maxDist)
        //     toRemove.insert(farton.entity);
    }

    // Instantiate new attack towards closest enemy
    if(t > firingRate) {
        t = 0;
        HUGO::ErrorOrType<EntityID> res = scene.instantiatePrefab(prefab);
        if(!res.isError()) {
            // TransformComponent& tr = scene.getComponentConst<TransformComponent>(res.getValue());
            const WorldTransformComponent& playerTr = scene.getComponentConst<WorldTransformComponent>(playerID);

            HUGO::Vector3 target = findClosestEnemy(playerTr.worldPosition);

            scene.modifyComponent<WorldTransformComponent>(res.getValue(), 
                [&target, &playerTr, this](WorldTransformComponent& worldTr) {
                    worldTr.worldRotation = HUGO::lookAt(
                        worldTr.worldRotation.forward(),
                        (target - playerTr.worldPosition), 
                        HUGO::Vector3(0,1,0)
                    ); // no need to normalize

                    worldTr.worldPosition = 
                        playerTr.worldPosition + instantiateRadius * worldTr.worldRotation.forward();
                    worldTr.worldPosition.y += 0.5f;
            });
            
        }
    }

}

void FartonSystem::update(uint32_t) {
    try {
        for(EntityID id : toRemove) {
            std::cout << "Borrando entidad " << id << "\n";
            scene.removeEntity(id);
        }
    }
    catch(std::exception e) {
        std::cout << "Fallo al borrar entidad: " << e.what() << '\n';
    }

    toRemove.clear();
}

HUGO::Vector3 FartonSystem::findClosestEnemy(HUGO::Vector3 pos) {
    float closestDist = FLT_MAX;
    HUGO::Vector3 closestPos = pos + HUGO::Vector3(FLT_MIN, 0,0);
    for(auto pack : scene.query<EnemyTag, WorldTransformComponent>()) {
        float dist = (pack.getConst<WorldTransformComponent>().worldPosition - pos).length();
        if(dist < closestDist) {
            closestPos = pack.getConst<WorldTransformComponent>().worldPosition;
            closestDist = dist;
        }
    }
    if(closestDist == FLT_MAX) return pos;
    return closestPos;
}
