#include "AudioEventsSystem.h"

#include "DynamicTrackMessage.h"
#include "HugoTypes.h"
#include "LuaBinder.h"

void 
AudioEventsSystem::init() {

}

void 
AudioEventsSystem::onLoad() {
    LuaBinder& luaBinder = LuaBinder::getInstance();
    luaBinder.registerMethod<AudioEventsSystem, void, HUGO::String>(*this, &AudioEventsSystem::sendToggleTrack, "toggle");
}

void 
AudioEventsSystem::update(uint32_t dt) {

}

void 
AudioEventsSystem::sendToggleTrack(HUGO::String name) {
    DynamicTrackMessage dynMsg;
    dynMsg.action = TOGGLE;
    dynMsg.trackName = name;

    scene.sendMessage(dynMsg);
}
