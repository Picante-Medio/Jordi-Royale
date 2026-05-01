#include "PauseSystem.h"

#include "ButtonComponent.h"

#include "ChangeSceneMessage.h"

void
PauseSystem::initResume(ResumeTag& resume){

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
PauseSystem::initExit(ExitTag& exit){

    scene.modifyComponent<ButtonComponent>(exit.entity, [this](ButtonComponent& but){

        but.onClickCallback = [this](){
            ChangeSceneMessage message;
            message.sceneName = "menu_scene";
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
    scene.onAddComponent<ResumeTag>().connect(this, &PauseSystem::initResume);
    scene.onAddComponent<ExitTag>().connect(this, &PauseSystem::initExit);
}

void 
PauseSystem::update(uint32_t){
    
}

void 
PauseSystem::fixedUpdate(uint32_t){

}