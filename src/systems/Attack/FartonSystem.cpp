#include <cfloat>
#include <exception>
#include <limits>
#include <set>
#include <exception>

#include "FartonSystem.h"
#include "FartonComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "ColliderComponent.h"
#include "EnemyTag.h"

void FartonSystem::init() {

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
    for(auto pack : scene.query<FartonComponent, TransformComponent>()) {
        const FartonComponent farton = pack.getConst<FartonComponent>();
        const TransformComponent tr = pack.getConst<TransformComponent>();

        HUGO::Vector3 dist = tr.rotation.forward() * farton.speed * dt * 0.001f;
        
        pack.modify<TransformComponent>([dist](TransformComponent& tr) {
            tr.position += dist;
        });
        pack.modify<FartonComponent>([dist](FartonComponent& farton) {
            farton.distance += dist.length();
            // std::cout << "Distancia recorrida del farton " << farton.entity << " : " << farton.distance << "\n";
        });
    }


    // Remove overdue attacks
    for(auto pack : scene.query<FartonComponent, ColliderComponent>()) {
        // Collided with anything
        const ColliderComponent collider = pack.getConst<ColliderComponent>();
        if(!collider.getCollisionInfo().empty())
            toRemove.insert(collider.entity);

        // Exceeded max distance
        const FartonComponent farton = pack.getConst<FartonComponent>();
        if(farton.distance > farton.maxDist)
            toRemove.insert(farton.entity);

        // Uncomment to ignore collisions with player
        // std::vector<EntityID> info = collider.getCollisionInfo();
        // if(info.empty()) continue;

        // bool destroy = false;
        // for(auto it = info.begin(); it != info.end() && !destroy; ++it)
        //     destroy = *it != playerID;
        // if(destroy) scene.removeEntity(collider.entity);
    }


    // Exceeded max distance
    // for(auto pack : scene.query<FartonComponent>()) {
    //     const FartonComponent farton = pack.getConst<FartonComponent>();
    //     if(farton.distance > farton.maxDist)
    //         scene.removeEntity(farton.entity);
    // }

    // Instantiate new attack towards closest enemy
    if(t > firingRate) {
        t = 0;
        HUGO::ErrorOrType<EntityID> res = scene.instantiatePrefab(prefab);
        if(!res.isError()) {
            TransformComponent& tr = scene.getComponent<TransformComponent>(res.getValue());
            const TransformComponent& playerTr = scene.getComponentConst<TransformComponent>(playerID);

            HUGO::Vector3 target = findClosestEnemy(playerTr.position);
            HUGO::Vector3 tmp = (target - playerTr.position);
            tr.rotation = HUGO::lookAt(tr.rotation.forward(),(target - playerTr.position), HUGO::Vector3(0,1,0)); // no need to normalize
      
            tr.position = playerTr.position + instantiateRadius * tr.rotation.forward();
            tr.position.y += 0.5f;
            // std::cout << "Farton instanciado en" << tr.position.x << " " << tr.position.y << " " << tr.position.z << "\n";
        }
    }

}

void FartonSystem::update(uint32_t) {

    for(EntityID id : toRemove) {
        try {
            std::cout << "Antes... \n";
            scene.removeEntity(id);
            std::cout << "Despues... \n";
        }
        catch(std::exception e) {std::cout << "Vaya... " << e.what() << '\n';}

    }
    toRemove.clear();
}

HUGO::Vector3 FartonSystem::findClosestEnemy(HUGO::Vector3 pos) {
    float closestDist = FLT_MAX;
    HUGO::Vector3 closestPos = pos + HUGO::Vector3(FLT_MIN, 0,0);
    for(auto pack : scene.query<EnemyTag, TransformComponent>()) {
        float dist = (pack.getConst<TransformComponent>().position - pos).length();
        if(dist < closestDist) {
            closestPos = pack.getConst<TransformComponent>().position;
            closestDist = dist;
        }
    }
    // std::cout << "Enemigo detectado en " << closestPos.x << " " << closestPos.y << " " << closestPos.z << " A distancia " << closestDist << "\n";
    if(closestDist == FLT_MAX) return pos;
    return closestPos;
}
