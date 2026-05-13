#include "ProgressionSystem.h"

#include "ClockTag.h"
#include "TextComponent.h"
#include "ChangeEnemyDensityMessage.h"
#include "IncreaseEnemyLevelMessage.h"
#include "SpawnBossMessage.h"
#include "ChangeSceneMessage.h"
#include "PanelComponent.h"
#include "TransformComponent.h"
#include "UpgradesManager.h"

void 
ProgressionSystem::onLoad(){
    
    scene.query<ClockTag, PanelComponent>().begin()->modify<PanelComponent>([](PanelComponent& panel){
            panel.isVisible = true;
    });

}

void 
ProgressionSystem::init(){
    scene.subscribe<ChangeSceneMessage>([this](std::shared_ptr<HUGO::Message> message) {
        std::shared_ptr<ChangeSceneMessage> m = std::static_pointer_cast<ChangeSceneMessage>(message);
        scene.query<ClockTag, PanelComponent>().begin()->modify<PanelComponent>([m](PanelComponent& panel){
            panel.isVisible = false;
        });
    });

    UpgradesManager::Instance().resetTime();
}

void 
ProgressionSystem::update(uint32_t dt){

    //------Time managing------
    miliseconds += dt;

    while(miliseconds >= 1000){
        seconds++;
        miliseconds -= 1000;
    }

    // not a while because the game should NEVER have 120 seconds between 2 given frames
    if(seconds >= 60){
        minutes++;
        if(!waveActive) minutesToNextWave--;
        else currentWaveMinutesLeft--;
        minutesUntilBoss--;
        seconds -= 60;
    }

    if(minutes >= 60){
        hours++;
        minutes -= 60;
    }

    // Update singleton
    UpgradesManager::Instance().setMiliseconds(miliseconds);
    UpgradesManager::Instance().setSeconds(seconds);
    UpgradesManager::Instance().setMinutes(minutes);
    UpgradesManager::Instance().setHours(hours);

    //------Clock UI update------
    
    for(auto& item : scene.query<ClockTag, TextComponent>()){

        // Update clock
        item.modify<TextComponent>([this](TextComponent& text){

            HUGO::String sHours = "";
            HUGO::String sMinutes = "";
            HUGO::String sSeconds = "";
            HUGO::String sMilisenconds = "";

            if(hours < 10) sHours += "0";
            if(minutes < 10) sMinutes += "0";
            if(seconds < 10) sSeconds += "0";
            if(miliseconds < 100) sMilisenconds += "0";
            if(miliseconds < 10) sMilisenconds += "0";

            sHours += std::to_string(hours);
            sMinutes += std::to_string(minutes);
            sSeconds += std::to_string(seconds);
            sMilisenconds += std::to_string(miliseconds);

            HUGO::String timeText = sHours + ":" + sMinutes + ":" + sSeconds + ":" + sMilisenconds;
            text.text = timeText;
        });
    }


    //------Wave managing------

    if(!waveActive && minutesToNextWave <= 0){
        changeEnemyDensity(true);
        currentWaveMinutesLeft = waveMinutesDuration;
        waveActive = true;
        wavesUntilEnemyLevelUp--;
    }

    if(waveActive && currentWaveMinutesLeft <= 0){
        changeEnemyDensity(false);
        minutesToNextWave = minutesBetweenWaves;
        waveActive = false;
    }

    //------Enemy level managing------

    if(wavesUntilEnemyLevelUp <= 0){
        wavesUntilEnemyLevelUp = wavesToEnemyLevelUp;
        IncreaseEnemyLevelMessage msg;
        scene.sendMessage<IncreaseEnemyLevelMessage>(msg);
    }

    //------Boss managing------
    if(minutesUntilBoss <= 0){
        minutesUntilBoss = minutesBetweenBosses;
        SpawnBossMessage msg;
        scene.sendMessage<SpawnBossMessage>(msg);
    }
}

void 
ProgressionSystem::fixedUpdate(uint32_t){

}

void
ProgressionSystem::changeEnemyDensity(bool increase){
    if(increase){
        ChangeEnemyDensityMessage msg;
        msg.milisecondsBetweenSpawns = regularSpawnRate/wavemultiplier;
        scene.sendMessage<ChangeEnemyDensityMessage>(msg);
        wavemultiplier++;
    }
    else{
        ChangeEnemyDensityMessage msg;
        msg.milisecondsBetweenSpawns = regularSpawnRate;
        scene.sendMessage<ChangeEnemyDensityMessage>(msg);
        regularSpawnRate -= enemyTimeReductionBetweenWaves;
    }
}
