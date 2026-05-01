#include "DamageSystem.h"
#include "HPComponent.h"
#include "DamageComponent.h"
#include "PlayerTag.h"
#include "ColliderComponent.h"
#include "EnemyTag.h"
#include "EnemyDeadMessage.h"
#include "PlayerDeadMessage.h"
#include "HealPlayerMessage.h"

void DamageSystem::init() {
    scene.subscribe<HealPlayerMessage>([this](std::shared_ptr<HUGO::Message> message){
        std::shared_ptr<HealPlayerMessage> m = std::static_pointer_cast<HealPlayerMessage>(message);
        changeHP(playerID, m->healPoints);
    });
}

void DamageSystem::onLoad() {

}

void DamageSystem::update(uint32_t) {
    playerID = scene.query<PlayerTag>().begin()->getConst<PlayerTag>().entity;
    for(EntityID id : scene.getComponent<ColliderComponent>(playerID).getCollisionInfo()){
        if(scene.hasComponent<DamageComponent>(id) && scene.getComponent<DamageComponent>(id).DamType == DamageComponent::Enemy){
            const DamageComponent& damage = scene.getComponent<DamageComponent>(id);
            HPComponent& playerHP = scene.getComponent<HPComponent>(playerID);
            changeHP(playerID, -damage.Damage);
            if(playerHP.CurrentHP <= 0){
                PlayerDeadMessage m;
                m.player = playerID;
                scene.sendMessage<PlayerDeadMessage>(m);
            }
        }
    }
        
    for(auto enemy : scene.query<HPComponent, ColliderComponent, EnemyTag>()){
        const ColliderComponent& collider = enemy.getConst<ColliderComponent>();
        if(collider.collisionInfo.empty()) continue;
        
        for(EntityID id : collider.getCollisionInfo()){
            if(scene.hasComponent<DamageComponent>(id) && scene.getComponent<DamageComponent>(id).DamType == DamageComponent::Player){
                const DamageComponent& damage = scene.getComponent<DamageComponent>(id);
                enemy.modify<HPComponent>([&damage, this] (HPComponent& hp){
                    changeHP(hp.entity, -damage.Damage);
                    if(hp.CurrentHP <= 0){
                        EnemyDeadMessage m;
                        m.enemy = hp.entity;
                        scene.sendMessage<EnemyDeadMessage>(m);
                    }
                });
            }
        }
    }
    
}
void DamageSystem::changeHP(EntityID id, HUGO::Int hp){
    HPComponent& entity = scene.getComponent<HPComponent>(id);
    entity.CurrentHP += hp;
    if(entity.CurrentHP > entity.HPMax) entity.CurrentHP = entity.HPMax;
}

void DamageSystem::fixedUpdate(uint32_t) {
    
}
