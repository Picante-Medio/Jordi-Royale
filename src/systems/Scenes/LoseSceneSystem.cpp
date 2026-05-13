#include "LoseSceneSystem.h"
#include "AnimationComponent.h"
#include "ButtonComponent.h"
#include "ChangeSceneMessage.h"

void 
LoseSceneSystem::init(){
    scene.onAddComponent<ResumeTag>().connect(this, &LoseSceneSystem::initResume);
    scene.onAddComponent<ExitTag>().connect(this, &LoseSceneSystem::initExit);
}

void 
LoseSceneSystem::onLoad() {
    for(auto enemy : scene.query<AnimationComponent>()) {
        enemy.modify<AnimationComponent>([](AnimationComponent& ac){
            ac.addAnimation("Idle", true);
            ac.setEnabled("Idle", true);
        });
    }
}

void
LoseSceneSystem::initResume(ResumeTag& resume){

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
LoseSceneSystem::initExit(ExitTag& exit){

    scene.modifyComponent<ButtonComponent>(exit.entity, [this](ButtonComponent& but){

        but.onClickCallback = [this](){
            ChangeSceneMessage message;
            message.sceneName = "main_menu";
            message.destroyCurrent = true;

            scene.sendMessage<ChangeSceneMessage>(message);
        };
    });
}
