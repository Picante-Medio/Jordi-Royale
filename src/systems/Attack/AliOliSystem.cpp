#include "AliOliSystem.h"
#include "ColliderComponent.h"
#include "RenderComponent.h"
#include "DamageComponent.h"
#include "AliOliTag.h"
#include "UpdateAliOliWeaponMessage.h"

void 
AliOliSystem::init(){
    scene.subscribe<UpdateAliOliWeaponMessage>([this](std::shared_ptr<HUGO::Message> message){
        if(!active){
            for(auto item : scene.query<AliOliTag, RenderComponent, DamageComponent>()){
                item.modify<RenderComponent>([](RenderComponent& rc){
                    //rc.isVisible = true;
                });

                item.modify<DamageComponent>([](DamageComponent& dam){
                    dam.DamType = DamageComponent::Player;
                });
            }
            active = true;
        }

        std::shared_ptr<UpdateAliOliWeaponMessage> m = std::static_pointer_cast<UpdateAliOliWeaponMessage>(message);
        damage += m->damageToAdd;
        count += m->countToAdd;

        for(auto item : scene.query<AliOliTag, DamageComponent>()){

                item.modify<DamageComponent>([this](DamageComponent& dam){
                    dam.Damage = damage * count;
                });
            }
    });
}

void 
AliOliSystem::onLoad(){

}

void 
AliOliSystem::fixedUpdate(uint32_t dt){

}

void 
AliOliSystem::update(uint32_t){

}