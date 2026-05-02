#include <math.h>

#include "PlayerMovementSystem.h"
#include "HugoMath.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "SpeedComponent.h"
#include "PlayerComponent.h"
#include "CameraPivotTag.h"
#include "CameraComponent.h"

void PlayerMovementSystem::init(){
    
    scene.getInput()->registerAction("Forward", HUGO::KeyCode::W);
    scene.getInput()->registerAction("Backward", HUGO::KeyCode::S);
    scene.getInput()->registerAction("Right", HUGO::KeyCode::D);
    scene.getInput()->registerAction("Left", HUGO::KeyCode::A);
    // Will be KeyCode::SPACE as soon as changes in HUGO are brought to main
    scene.getInput()->registerAction("Jump", HUGO::KeyCode::SPACE);
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

    // * TESTING METHOD CALL

    scene.query<TransformComponent, PlayerComponent>()[0].modify<TransformComponent>([this](TransformComponent& trans){
        updateCamera(trans);
    });
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

    for(auto& item : scene.query<PlayerComponent, RigidBodyComponent, SpeedComponent, TransformComponent>()){
        item.modify<RigidBodyComponent>([&item, velocity, jumpDirection](RigidBodyComponent& rb){
            // horizontal movement
            rb.applyForce(velocity * item.getConst<SpeedComponent>().speed);

            // vertical movement
            if(rb.getLinearVelocity().y < 0.05f && rb.getLinearVelocity().y > -0.05f)
                rb.applyForce(jumpDirection * item.getConst<PlayerComponent>().jumpPower);

            // rotation
            item.modify<TransformComponent>([rb, velocity](TransformComponent& trans){
                if(velocity == HUGO::Vector3()) return;
                HUGO::Vector3 rotation = HUGO::Vector3(0, 0, 1).cross(velocity);
                HUGO::Float wValue = sqrt(pow(HUGO::Vector3(0, 0, 1).length(), 2) * pow(velocity.length(), 2)) + velocity.z;
                trans.setRotation(HUGO::Quaternion(wValue, rotation.x, rotation.y, rotation.z));

                // Needed because previous calculations doesn't work properly when going forward and I don't know math
                if(trans.getRotation() == HUGO::Quaternion(0, 0, 0, 0))
                    trans.setRotation(HUGO::Quaternion(HUGO::Degree(180), HUGO::Vector3(0, 1, 0)));
            });

            rb.setAngularVelocity(HUGO::Vector3());
        });
    }

}

// * TESTING METHOD

void
PlayerMovementSystem::updateCamera(TransformComponent& playerTrans){
    scene.query<TransformComponent, CameraComponent>()[0].modify<TransformComponent>([this, playerTrans](TransformComponent& trans){
        trans.setPosition(playerTrans.getPosition() + HUGO::Vector3(0, yOffset, zOffset));
    });
}
