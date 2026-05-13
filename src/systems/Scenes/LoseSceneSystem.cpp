#include "LoseSceneSystem.h"
#include "AnimationComponent.h"
#include "ButtonComponent.h"
#include "ChangeSceneMessage.h"
#include "TextComponent.h"
#include "UpgradesManager.h"

void 
LoseSceneSystem::init(){
    scene.onAddComponent<ResumeTag>().connect(this, &LoseSceneSystem::initResume);
    scene.onAddComponent<ExitTag>().connect(this, &LoseSceneSystem::initExit);
    scene.onAddComponent<ClockTag>().connect(this, &LoseSceneSystem::initTime);
    scene.onAddComponent<EnemyTag>().connect(this, &LoseSceneSystem::initEnemyCount);
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

void 
LoseSceneSystem::initTime(ClockTag& time){
    scene.modifyComponent<TextComponent>(time.entity, [this](TextComponent& text){
        
        HUGO::String sHours = "";
        HUGO::String sMinutes = "";
        HUGO::String sSeconds = "";
        HUGO::String sMilisenconds = "";

        UpgradesManager ins = UpgradesManager::Instance();

        if(ins.getHours() < 10) sHours += "0";
        if(ins.getMinutes() < 10) sMinutes += "0";
        if(ins.getSeconds() < 10) sSeconds += "0";
        if(ins.getMiliseconds() < 100) sMilisenconds += "0";
        if(ins.getMiliseconds() < 10) sMilisenconds += "0";

        sHours += std::to_string(ins.getHours());
        sMinutes += std::to_string(ins.getMinutes());
        sSeconds += std::to_string(ins.getSeconds());
        sMilisenconds += std::to_string(ins.getMiliseconds());

        HUGO::String timeText = "Time: " + sHours + ":" + sMinutes + ":" + sSeconds + ":" + sMilisenconds;
        text.text = timeText;
    });
}

void 
LoseSceneSystem::initEnemyCount(EnemyTag& count){
    scene.modifyComponent<TextComponent>(count.entity, [this](TextComponent& text){
        
        HUGO::String countText = "Enemies defeated: ";
        countText += std::to_string(UpgradesManager::Instance().getEnemies());
        text.text = countText;
    });
}