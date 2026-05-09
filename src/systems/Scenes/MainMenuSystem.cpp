#include "MainMenuSystem.h"
#include "AnimationComponent.h"
#include "ButtonComponent.h"
#include "ChangeSceneMessage.h"

void 
MainMenuSystem::init(){
    scene.onAddComponent<ResumeTag>().connect(this, &MainMenuSystem::initResume);
    scene.onAddComponent<ExitTag>().connect(this, &MainMenuSystem::initExit);
}

void 
MainMenuSystem::onLoad() {
    for(auto jordi : scene.query<AnimationComponent>()) {
        jordi.modify<AnimationComponent>([](AnimationComponent& ac){
            ac.addAnimation("Idle", true);
            ac.setEnabled("Idle", true);
        });
    }
}

void
MainMenuSystem::initResume(ResumeTag& resume){

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
MainMenuSystem::initExit(ExitTag& exit){

    scene.modifyComponent<ButtonComponent>(exit.entity, [this](ButtonComponent& but){

        but.onClickCallback = [this](){
            scene.exitGame();
        };
    });
}
