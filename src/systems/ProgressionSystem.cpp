#include "ProgressionSystem.h"

#include "ClockTag.h"
#include "TextComponent.h"

#include <iostream>

void 
ProgressionSystem::onLoad(){

}

void 
ProgressionSystem::init(){
    
}

void 
ProgressionSystem::update(uint32_t dt){

    miliseconds += dt;

    while(miliseconds >= 1000){
        seconds++;
        miliseconds -= 1000;
    }

    // not a while because the game should NEVER have 120 seconds between 2 given frames
    if(seconds >= 60){
        minutes++;
        seconds -= 60;
    }

    if(minutes >= 60){
        hours++;
        minutes -= 60;
    }
    
    for(auto& item : scene.query<ClockTag, TextComponent>()){

        // Update clock
        item.modify<TextComponent>([this](TextComponent& text){

            HUGO::String timeText = std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(miliseconds);
            text.text = timeText;
        });
    }
}

void 
ProgressionSystem::fixedUpdate(uint32_t){

}