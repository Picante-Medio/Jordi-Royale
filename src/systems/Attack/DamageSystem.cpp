#include "DamageSystem.h"
#include "EcsTypes.h"
#include "HPComponent.h"
#include "DamageComponent.h"
#include "PlayerComponent.h"
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

void DamageSystem::update(uint32_t dt) {
    playerID = scene.query<PlayerComponent>().begin()->getConst<PlayerComponent>().entity;
    timeSinceCooldown += dt;

    for(EntityID id : scene.getComponent<ColliderComponent>(playerID).getCollisionInfo()){

        if(timeSinceCooldown < msCooldown) continue;
        if(scene.hasComponent<DamageComponent>(id) && scene.getComponentConst<DamageComponent>(id).DamType == DamageComponent::Enemy){
            const DamageComponent damage = scene.getComponentConst<DamageComponent>(id);
            changeHP(playerID, -damage.Damage);
            timeSinceCooldown = 0;
            HPComponent playerHP = scene.getComponentConst<HPComponent>(playerID);
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
            if(scene.hasComponent<DamageComponent>(id) && scene.getComponentConst<DamageComponent>(id).DamType == DamageComponent::Player){
                const DamageComponent& damage = scene.getComponentConst<DamageComponent>(id);
                changeHP(collider.entity, -damage.Damage);
                HPComponent hp = enemy.getConst<HPComponent>();
                if(hp.CurrentHP <= 0){
                    EnemyDeadMessage m;
                    m.enemy = hp.entity;
                    scene.sendMessage<EnemyDeadMessage>(m);
                }
            }
        }
    }
    
}
void DamageSystem::changeHP(EntityID id, HUGO::Int hp){
    scene.modifyComponent<HPComponent>(id, [hp](HPComponent& entHp){
        entHp.CurrentHP += hp;
        if(entHp.CurrentHP > entHp.HPMax) entHp.CurrentHP = entHp.HPMax;
    });
}

void DamageSystem::fixedUpdate(uint32_t) {
    
}
