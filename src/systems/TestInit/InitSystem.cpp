#include "InitSystem.h"

#include "JordiRandom.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "PlayerComponent.h"
#include "SpeedComponent.h"
#include "HPComponent.h"
#include "ColliderComponent.h"
#include "RigidBodyComponent.h"
#include "CameraComponent.h"

void 
InitSystem::onLoad(){

}

void 
InitSystem::init(){

    //RNG
    JordiRandom::Instance().Init();

    // Jordi

    EntityID jordi = scene.createEntity();

    scene.addComponent<TransformComponent>(jordi, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(0, 0.5, 0));
        trans.setRotation(HUGO::Vector4(0, 0, 0, 1));
        trans.setScale(HUGO::Vector3(1, 1, 1));
    });

    scene.addComponent<RenderComponent>(jordi, [](RenderComponent& rc){
        rc.setMeshName("jordi.glb");
        rc.setMaterialName("");
    });

    scene.addComponent<PlayerComponent>(jordi, [](PlayerComponent& pc){
        pc.jumpPower = 500.0f;
    });

    scene.addComponent<SpeedComponent>(jordi, [](SpeedComponent& sp){
        sp.speed = 50;
    });

    scene.addComponent<HPComponent>(jordi, [](HPComponent& hp){
        hp.HPMax = 100;
        hp.CurrentHP = 100;
    });


    scene.addComponent<ColliderComponent>(jordi, [](ColliderComponent& col){
        col.info = HUGO::CylinderColliderInfo({HUGO::Vector3(0.5, 1, 0.5)});
        col.restitution = 0;
        col.friction = 0.5;
        col.positionOffset = HUGO::Vector3(0, 1, 0);
        col.rotationOffset = HUGO::Vector4(0, 0, 0, 1);
        col.active = true;
        col.useGizmo = true;
    });

    scene.addComponent<RigidBodyComponent>(jordi, [](RigidBodyComponent& rb){
        rb.setMass(5);
        rb.setLinearDamping(0.5);
        rb.setAngularDamping(0.5);
        rb.setLinearVelocity(HUGO::Vector3(0, 0, 0));
        rb.setAngularVelocity(HUGO::Vector3(0, 0, 0));
        rb.setLinearSleepingThreshold(0.8);
        rb.setAngularSleepingThreshold(1);
        rb.dontRotateWithPhysicsOnDynamic = true;
    });

    // Camera

    EntityID camera = scene.createEntity();

    scene.addComponent<TransformComponent>(camera, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(0, 0.8, 4));
        trans.setRotation(HUGO::Vector4(0, 0, 0, 1));
        trans.setScale(HUGO::Vector3(1, 1, 1));
    });

    scene.addComponent<CameraComponent>(camera, [](CameraComponent& cam){
        cam.setProjectionType(HUGO::ProjectionType(0));
        cam.setFOVY(60);
        cam.setNearClip(1);
        cam.setFarClip(10000);
        cam.setOrthographicDimensions(10, 10);
        cam.setMain(true);
        cam.setClearColor(HUGO::Vector4(0, 0, 0, 1));
    });

    // Floor

    EntityID floor = scene.createEntity();

    scene.addComponent<TransformComponent>(floor, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(0, -0.25, 0));
        trans.setRotation(HUGO::Vector4(0, 0, 0, 1));
        trans.setScale(HUGO::Vector3(17.32, 0.75, 13.2));
    });

    scene.addComponent<ColliderComponent>(floor, [](ColliderComponent& col){
        col.info = HUGO::BoxColliderInfo({HUGO::Vector3(7.7, 0.5, 8)});
        col.setRestitution(0);
        col.setFriction(1.5);
        col.setPositionOffset(HUGO::Vector3(0, 0, 0));
        col.setRotationOffset(HUGO::Vector4(0, 0, 0, 1));
        col.setActive(false);
        col.useGizmo = false;
    });

    scene.addComponent<RigidBodyComponent>(floor, [](RigidBodyComponent& rb){
        rb.setMass(0);
        rb.setBodyType(HUGO::BodyType::STATIC);
        rb.setLinearDamping(0.5);
        rb.setAngularDamping(0.5);
        rb.setLinearSleepingThreshold(0.8);
        rb.setAngularSleepingThreshold(1);
    });

    scene.addComponent<RenderComponent>(floor, [](RenderComponent& rc){
        rc.setMeshName("cube.mesh");
    });
}

void 
InitSystem::update(uint32_t){
    
}

void 
InitSystem::fixedUpdate(uint32_t){
    
}
