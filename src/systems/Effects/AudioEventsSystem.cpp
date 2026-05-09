#include "AudioEventsSystem.h"

#include <algorithm>

#include "DynamicTrackMessage.h"
#include "EcsTypes.h"
#include "DynamicAudioComponent.h"
#include "AudioComponent.h"

void 
AudioEventsSystem::init() {

}

void 
AudioEventsSystem::onLoad() {

}

void 
AudioEventsSystem::update(uint32_t dt) {
    DynamicTrackMessage message;
    message.action = TOGGLE;

    if(scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::H)) {
        message.trackName = "base";
    }

    if(scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::J)) {
        message.trackName = "main";
    }

    if(scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::K)) {
        message.trackName = "hi-hat";
    }

    if(scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::L)) {
        message.trackName = "kick-snare";
    }

    if(message.trackName != "") 
        scene.sendMessage(message);
}
