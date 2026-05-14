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
            scene.query<AliOliTag, 
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