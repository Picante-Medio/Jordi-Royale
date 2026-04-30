#include "DamageSystem.h"
#include "HPComponent.h"
#include "DamageComponent.h"
#include "PlayerTag.h"
#include "ColliderComponent.h"
#include "EnemyComponent.h"

void DamageSystem::init() {
    

}

void DamageSystem::onLoad() {

}

void DamageSystem::update(uint32_t) {
    playerID = scene.query<PlayerTag>().begin()->getConst<PlayerTag>().entity;
    for(EntityID id : scene.getComponent<ColliderComponent>(playerID).getCollisionInfo()){
        if(scene.hasComponent<DamageComponent>(id) && scene.getComponent<DamageComponent>(id).DamType == DamageComponent::Enemy){
            const DamageComponent& damage = scene.getComponent<DamageComponent>(id);
            scene.getComponent<HPComponent>(playerID).CurrentHP -= scene.getComponent<DamageComponent>(id).Damage;
        }
    }
        
    for(auto enemy : scene.query<HPComponent, ColliderComponent>()){
        const ColliderComponent& collider = enemy.getConst<ColliderComponent>();
        if(collider.collisionInfo.empty()) continue;
        
        for(EntityID id : collider.getCollisionInfo()){
            if(scene.hasComponent<DamageComponent>(id) && scene.getComponent<DamageComponent>(id).DamType == DamageComponent::Player){
                const DamageComponent& damage = scene.getComponent<DamageComponent>(id);
                enemy.modify<HPComponent>([&damage] (HPComponent& hp){
                    hp.CurrentHP -= damage.Damage;
            });
            }
        }
    }
    
}
void DamageSystem::heal(std::shared_ptr<HUGO::Message> m){
    
}

void DamageSystem::fixedUpdate(uint32_t) {
    
}
