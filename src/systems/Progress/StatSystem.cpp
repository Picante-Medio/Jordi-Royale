#include "StatSystem.h"
#include "HUGO.h"
#include "PlayerComponent.h"
#include "TextComponent.h"
#include "PanelComponent.h"
#include "ChangeSceneMessage.h"

#include "HPTextTag.h"
#include "XPTextTag.h"

void 
StatSystem::onLoad(){
    scene.query<HPTextTag, PanelComponent>().begin()->modify<PanelComponent>([](PanelComponent& panel){
            panel.isVisible = true;
    });
    scene.query<XPTextTag, PanelComponent>().begin()->modify<PanelComponent>([](PanelComponent& panel){
            panel.isVisible = true;
    });
}

void 
StatSystem::init(){
    scene.onUpdateComponent<HPComponent>().connect(this, &StatSystem::updateHPText);
    scene.onUpdateComponent<LevelComponent>().connect(this, &StatSystem::updateXPText);

    scene.subscribe<ChangeSceneMessage>([this](std::shared_ptr<HUGO::Message> message) {
        std::shared_ptr<ChangeSceneMessage> m = std::static_pointer_cast<ChangeSceneMessage>(message);
        scene.query<HPTextTag, PanelComponent>().begin()->modify<PanelComponent>([m](PanelComponent& panel){
            panel.isVisible = false;
        });
    });

    scene.subscribe<ChangeSceneMessage>([this](std::shared_ptr<HUGO::Message> message) {
        std::shared_ptr<ChangeSceneMessage> m = std::static_pointer_cast<ChangeSceneMessage>(message);
        scene.query<XPTextTag, PanelComponent>().begin()->modify<PanelComponent>([m](PanelComponent& panel){
            panel.isVisible = false;
        });
    });

}

void 
StatSystem::update(uint32_t){

}

void 
StatSystem::fixedUpdate(uint32_t){

}

void 
StatSystem::updateHPText(HPComponent& hp){
    if(scene.hasComponent<PlayerComponent>(hp.entity)){
        scene.query<HPTextTag, TextComponent>().begin()->modify<TextComponent>([hp](TextComponent& text){
            HUGO::String result = "HP: ";
            result += std::to_string(hp.CurrentHP);
            result += " / ";
            result += std::to_string(hp.HPMax);

            text.text = result;
        });
    }
}

void 
StatSystem::updateXPText(LevelComponent& xp){
    if(scene.hasComponent<PlayerComponent>(xp.entity)){
        scene.query<XPTextTag, TextComponent>().begin()->modify<TextComponent>([xp](TextComponent& text){
            HUGO::String result = "XP: ";
            result += std::to_string(xp.currentExperience);
            result += " / ";
            result += std::to_string(xp.experienceToNextLevel);
            result += "\nLevel: ";
            result += std::to_string(xp.level);

            text.text = result;
        });
    }
}