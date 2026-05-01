#include "PauseSystem.h"

#include "ButtonComponent.h"

#include "ChangeSceneMessage.h"

void
PauseSystem::initButtons(ResumeTag& resume){

    scene.modifyComponent<ButtonComponent>(resume.entity, [this](ButtonComponent& but){

        but.onClickCallback = [this](){
            ChangeSceneMessage message;
            message.sceneName = "main_scene";
            message.destroyCurrent = true;
    
            scene.sendMessage<ChangeSceneMessage>(message);
        };
    });
}

void 
PauseSystem::onLoad(){
    
}

void 
PauseSystem::init(){
    scene.onAddComponent<ResumeTag>().connect(this, &PauseSystem::initButtons);
}

void 
PauseSystem::update(uint32_t){
    
}

void 
PauseSystem::fixedUpdate(uint32_t){

}