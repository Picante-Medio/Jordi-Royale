#include "PlayerMovementSystem.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "SpeedComponent.h"
#include "JumpPowerComponent.h"
#include "PlayerTag.h"

void PlayerMovementSystem::init(){
    
    scene.getInput()->registerAction("Forward", {HUGO::KeyCode::W});
    scene.getInput()->registerAction("Backward", {HUGO::KeyCode::S});
    scene.getInput()->registerAction("Right", {HUGO::KeyCode::D});
    scene.getInput()->registerAction("Left", {HUGO::KeyCode::A});
    // Will be KeyCode::SPACE as soon as changes in HUGO are brought to main
    scene.getInput()->registerAction("Jump", {HUGO::KeyCode::Q});
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
    // TODO calculate rotation degrees
    // HUGO::Degree()

    // rigidboy is a cylinder, rotation is not needed
    for(auto& item : scene.query<TransformComponent, PlayerTag>()){
        item.modify<TransformComponent>([](TransformComponent& trans){
            // TODO trans.setRotation(HUGO::Quaternion())
        });
    }
}

void PlayerMovementSystem::fixedUpdate(uint32_t){

    HUGO::Vector3 velocity = HUGO::Vector3();

    // z-axis
    if(scene.getInput()->isActionPressed("Forward")) velocity += HUGO::Vector3(0, 0, 1);
    else if(scene.getInput()->isActionPressed("Backward")) velocity = velocity - HUGO::Vector3(0, 0, 1);

    // x-axis
    if(scene.getInput()->isActionPressed("Right")) velocity += HUGO::Vector3(1, 0, 0);
    else if(scene.getInput()->isActionPressed("Left")) velocity = velocity - HUGO::Vector3(0, 0, 1);

    // normalize
    velocity.normalize();

    for(auto& item : scene.query<RigidBodyComponent, SpeedComponent, JumpPowerComponent, PlayerTag>()){
        item.modify<RigidBodyComponent>([item, velocity](RigidBodyComponent& rb){
            // horizontal movement
            rb.applyForce(velocity * item.getConst<SpeedComponent>().speed);

            // vertical movement
            if(rb.getLinearVelocity().y == 0)
                rb.applyForce(HUGO::Vector3(0, 1, 0) * item.getConst<JumpPowerComponent>().power);
        });
    }
}