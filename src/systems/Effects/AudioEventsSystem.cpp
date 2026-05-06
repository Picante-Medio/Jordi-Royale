#include "AudioEventsSystem.h"
#include "DynamicTrackMessage.h"
#include "HugoInputCodes.h"

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

    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::H)) {
        message.trackName = "base";
    }

    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::J)) {
        message.trackName = "main";
    }

    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::K)) {
        message.trackName = "hi-hat";
    }

    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::L)) {
        message.trackName = "kick-snare";
    }
}
