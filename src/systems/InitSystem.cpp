#include "InitSystem.h"
#include "HugoMath.h"

#include "TransformComponent.h"
#include "RenderComponent.h"
#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "CameraComponent.h"
#include "PlayerTag.h"
#include "SpeedComponent.h"
#include "JumpPowerComponent.h"
#include "HPComponent.h"

void 
InitSystem::init(){
    EntityID floor = scene.createEntity();
    
    scene.addComponent<TransformComponent>(floor, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(10, 0, 0));
        trans.setScale(HUGO::Vector3(10, 10, 1));
    });

    scene.addComponent<RenderComponent>(floor, [](RenderComponent& rc){
        rc.setMeshName("cube.mesh");
    });

    scene.addComponent<ColliderComponent>(floor, [](ColliderComponent& col){
        col.info = HUGO::BoxColliderInfo{(HUGO::Vector3(5, 5, .5))};
        col.useGizmo = true;
    });

    scene.addComponent<RigidBodyComponent>(floor, [](RigidBodyComponent& rb){
        rb.setBodyType(HUGO::BodyType::STATIC);
    });

    EntityID jordi = scene.createEntity();

    scene.addComponent<TransformComponent>(jordi, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(0, 10, 0));
    });

    scene.addComponent<RenderComponent>(jordi, [](RenderComponent& rc){
        rc.setMeshName("cube.mesh");
    });

    scene.addComponent<ColliderComponent>(jordi, [](ColliderComponent& col){
        col.info = HUGO::CapsuleColliderInfo{(1, 2)};
    });
    
    scene.addComponent<RigidBodyComponent>(jordi, [](RigidBodyComponent& rb){
        rb.setBodyType(HUGO::BodyType::DYNAMIC);
    });
}

void 
InitSystem::onLoad(){

}

void 
InitSystem::update(uint32_t){

}

void 
InitSystem::fixedUpdate(uint32_t){

}