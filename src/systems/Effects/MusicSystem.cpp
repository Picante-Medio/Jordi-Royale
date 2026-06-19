#pragma once

#include "MusicSystem.h"

#include "PlayerComponent.h"
#include "DynamicTrackMessage.h"

void 
MusicSystem::onLoad(){

    DynamicTrackMessage dynMsg;
    DynamicTrackMessage dynMsg2;

    dynMsg.trackName = "chordstrack";
    dynMsg2.trackName = "basstrack";
    dynMsg.action = ACTIVATE;
    dynMsg2.action = ACTIVATE;

    scene.sendMessage(dynMsg);
    scene.sendMessage(dynMsg2);

    if(scene.query<PlayerComponent>().size() > 0){
        
        dynMsg.trackName = "melodytrack";
        dynMsg2.trackName = "arpegiotrack";

        dynMsg.action = ACTIVATE;
        dynMsg2.action = ACTIVATE;

        scene.sendMessage(dynMsg);
        scene.sendMessage(dynMsg2);
    }
}

void 
MusicSystem::init(){
    
}