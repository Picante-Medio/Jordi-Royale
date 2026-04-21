#include "PlayerMovementSystem.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "SpeedComponent.h"
#include "PlayerTag.h"

void PlayerMovementSystem::init(){

}

void PlayerMovementSystem::onLoad(){

}

void PlayerMovementSystem::update(uint32_t){

    for(auto& item : scene.query<RigidBodyComponent, ColliderComponent, SpeedComponent, PlayerTag>()){

    }
}

void PlayerMovementSystem::fixedUpdate(uint32_t){

}