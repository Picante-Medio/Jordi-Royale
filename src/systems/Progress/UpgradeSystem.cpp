#include "UpgradeSystem.h"
#include "ResumeTag.h"
#include "ButtonComponent.h"
#include "ChangeSceneMessage.h"

void UpgradeSystem::resumeGame(ResumeTag& tag) {
    scene.modifyComponent<ButtonComponent>(tag.entity, [this](ButtonComponent& button){
        button.onClickCallback = [this](){
            ChangeSceneMessage message;
            message.sceneName = "main_scene";
            message.destroyCurrent = true;

            scene.sendMessage<ChangeSceneMessage>(message);
        };
    });
}

void UpgradeSystem::init() {
    scene.onAddComponent<ResumeTag>().connect(this, &UpgradeSystem::resumeGame);
}

void UpgradeSystem::onLoad() {

}

void UpgradeSystem::fixedUpdate(uint32_t) {

}

void UpgradeSystem::update(uint32_t) {

}
