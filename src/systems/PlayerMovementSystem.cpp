#include "PlayerMovementSystem.h"
#include "HugoMath.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "SpeedComponent.h"
#include "JumpPowerComponent.h"
#include "PlayerTag.h"
#include "CameraPivotTag.h"

//*---Test includes---
#include "ColliderComponent.h"
#include "RenderComponent.h"

void PlayerMovementSystem::init(){

    // * TESTING: Floor for Jordi
    EntityID floor = scene.createEntity();

    scene.addComponent<TransformComponent>(floor, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(0, -3, -10));
    });

    scene.addComponent<ColliderComponent>(floor, [](ColliderComponent& col){
        col.info = HUGO::BoxColliderInfo({HUGO::Vector3(5, 1, 5)});
        col.useGizmo = true;
    });

    scene.addComponent<RigidBodyComponent>(floor, [](RigidBodyComponent& rb){
        rb.setBodyType(HUGO::STATIC);
    });

    EntityID JordiTest = scene.createEntity();

    scene.addComponent<TransformComponent>(JordiTest, [](TransformComponent& trans){
        trans.setPosition(HUGO::Vector3(0, 5, -10));
    });

    scene.addComponent<ColliderComponent>(JordiTest, [](ColliderComponent& col){
        col.info = HUGO::BoxColliderInfo({HUGO::Vector3(0.5, 0.5, 0.5)});
        col.useGizmo = true;
    });

    scene.addComponent<RigidBodyComponent>(JordiTest, [](RigidBodyComponent& rb){
        rb.setBodyType(HUGO::DYNAMIC);
        rb.setMass(5.0f);
    });

    scene.addComponent<PlayerTag>(JordiTest);
    scene.addComponent<SpeedComponent>(JordiTest, [](SpeedComponent& sp){
        sp.speed = 50;
    });
    scene.addComponent<JumpPowerComponent>(JordiTest);
    scene.addComponent<RenderComponent>(JordiTest, [](RenderComponent& rc){
        rc.meshName = "jordi.glb";
    });
    // * TESTING END
    
    scene.getInput()->registerAction("Forward", {HUGO::KeyCode::W});
    scene.getInput()->registerAction("Backward", {HUGO::KeyCode::S});
    scene.getInput()->registerAction("Right", {HUGO::KeyCode::D});
    scene.getInput()->registerAction("Left", {HUGO::KeyCode::A});
    // Will be KeyCode::SPACE as soon as changes in HUGO are brought to main
    scene.getInput()->registerAction("Jump", {HUGO::KeyCode::SPACE});
}

// every time the scene is loaded, the mouse position is registered again
void PlayerMovementSystem::onLoad(){
    lastMousePosition = HUGO::Vector2(scene.getInput()->getMouseRelativePosition().x, 
                                      scene.getInput()->getMouseRelativePosition().y);
}

void PlayerMovementSystem::update(uint32_t){

    HUGO::Vector2 currentMousePosition = HUGO::Vector2(scene.getInput()->getMouseRelativePosition().x, 
                                                       scene.getInput()->getMouseRelativePosition().y);

    HUGO::Vector2 diff = currentMousePosition - lastMousePosition;
    HUGO::Quaternion rotation = HUGO::Quaternion(HUGO::Radian(HUGO::Degree(diff.x * 360 * SENSIBILITY)), HUGO::Vector3(0, 1, 0))
                              * HUGO::Quaternion(HUGO::Radian(HUGO::Degree(diff.y * 360 * SENSIBILITY)), HUGO::Vector3(1, 0, 0));

    // rigidboy is a cylinder, rotation is not needed
    for(auto& item : scene.query<TransformComponent, CameraPivotTag>()){
        item.modify<TransformComponent>([rotation](TransformComponent& trans){
            trans.setRotation(trans.getRotation() * rotation);
        });
    }

    lastMousePosition = currentMousePosition;
}

void PlayerMovementSystem::fixedUpdate(uint32_t){

    HUGO::Vector3 velocity = HUGO::Vector3();
    HUGO::Vector3 jumpDirection = HUGO::Vector3();

    // z-axis
    if(scene.getInput()->isActionPressed("Forward")) velocity = velocity - HUGO::Vector3(0, 0, 1);
    else if(scene.getInput()->isActionPressed("Backward")) velocity += HUGO::Vector3(0, 0, 1);

    // x-axis
    if(scene.getInput()->isActionPressed("Right")) velocity += HUGO::Vector3(1, 0, 0);
    else if(scene.getInput()->isActionPressed("Left")) velocity = velocity - HUGO::Vector3(1, 0, 0);

    // Jump
    if(scene.getInput()->isActionPressed("Jump"))
        jumpDirection = HUGO::Vector3(0.f, 1.f, 0.f);

    // normalize
    velocity.normalize();

    for(auto& item : scene.query<RigidBodyComponent, SpeedComponent, JumpPowerComponent, PlayerTag, TransformComponent>()){
        item.modify<RigidBodyComponent>([&item, velocity, jumpDirection](RigidBodyComponent& rb){
            // horizontal movement
            rb.applyForce(velocity * item.getConst<SpeedComponent>().speed);

            // vertical movement
            if(rb.getLinearVelocity().y < 0.05f && rb.getLinearVelocity().y > -0.05f)
                rb.applyForce(jumpDirection * item.getConst<JumpPowerComponent>().power);

            // rotation
            item.modify<TransformComponent>([rb](TransformComponent& trans){
                // TODO trans.setRotation(HUGO::Quaternion());
            });
        });
    }
}
