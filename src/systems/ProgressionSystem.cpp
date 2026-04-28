#include "ProgressionSystem.h"

#include "ClockTag.h"
#include "TextComponent.h"
#include "IncreaseEnemyDensityMessage.h"
#include "DecreaseEnemyDensityMessage.h"
#include "IncreaseEnemyLevelMessage.h"

#include <iostream>

void 
ProgressionSystem::onLoad(){

}

void 
ProgressionSystem::init(){
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

    //------Clock UI update------
    
    for(auto& item : scene.query<ClockTag, TextComponent>()){

        // Update clock
        item.modify<TextComponent>([this](TextComponent& text){

            HUGO::String timeText = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(miliseconds);
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
        // TODO scene.instantiatePrefab(boss);
        minutesUntilBoss = minutesBetweenBosses;
    }
}

void 
ProgressionSystem::fixedUpdate(uint32_t){

}

void
ProgressionSystem::changeEnemyDensity(bool increase){
    if(increase){
        IncreaseEnemyDensityMessage msg;
        scene.sendMessage<IncreaseEnemyDensityMessage>(msg);
    }
    else{
        DecreaseEnemyDensityMessage msg;
        scene.sendMessage<DecreaseEnemyDensityMessage>(msg);
    }
}