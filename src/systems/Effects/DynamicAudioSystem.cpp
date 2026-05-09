#include "DynamicAudioSystem.h"

#include <cmath>
#include <memory>

#include "AudioComponent.h"
#include "TweenComponent.h"
#include "DynamicAudioComponent.h"
#include <DynamicTrackMessage.h>

void 
DynamicAudioSystem::init() {
    scene.subscribe<DynamicTrackMessage>([this](std::shared_ptr<HUGO::Message> m){
        std::shared_ptr<DynamicTrackMessage> message = std::static_pointer_cast<DynamicTrackMessage>(m);
        toggleTrack(message->trackName, message->action);
    });

    scene.onUpdateComponent<DynamicAudioComponent>().connect(this, &DynamicAudioSystem::onUpdateDyn);
}

void 
DynamicAudioSystem::onLoad() {
    for(auto pack : scene.query<DynamicAudioComponent, AudioComponent>()) {
        const DynamicAudioComponent& dyn = pack.getConst<DynamicAudioComponent>();

        trackEntities[dyn.audioName] = TrackEntity{dyn.entity, false};
        pack.modify<AudioComponent>([this, dyn](AudioComponent& ac){
            ac.audioName = dyn.audioName;
            ac.isPlaying = true;
            ac.loop = true;
            ac.volume = dyn.minVolume;
            ac.type = HUGO::MUSIC;
        });
    }
}

void 
DynamicAudioSystem::activateTrack(HUGO::String trackName) {
    if (trackEntities[trackName].active)
        return;

    std::cout << "Activated track " << trackName << "\n";
    trackEntities[trackName].active = true;
    activeCounter++;

    equalizeTracks();
}

void 
DynamicAudioSystem::deactivateTrack(HUGO::String trackName) {
    if (!trackEntities[trackName].active)
        return;

    std::cout << "Deactivated track " << trackName << "\n";
    trackEntities[trackName].active = false;
    activeCounter--;

    equalizeTracks();
}


void 
DynamicAudioSystem::equalizeTracks() {
    for (auto [key, track] : trackEntities) {
        const DynamicAudioComponent& dc = scene.getComponentConst<DynamicAudioComponent>(track.entity);
        scene.modifyComponent<AudioComponent>(track.entity, [this, &track, &dc](AudioComponent &ac) {
            if (!track.active || activeCounter == 0)
            scene.modifyComponent<TweenComponent>(track.entity, [this, &track, &ac, &dc](TweenComponent& tc) {
                tc.currentTweens.clear();
                tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                    ac,
                    &AudioComponent::volume,
                    ac.volume,
                    dc.minVolume,
                    dc.interpolationMiliseconds));
                });
            else
            scene.modifyComponent<TweenComponent>(track.entity, [this, &ac, &dc](TweenComponent& tc) {
                tc.currentTweens.clear();
                tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                    ac, 
                    &AudioComponent::volume, 
                    ac.volume, 
                    dc.maxVolume / std::sqrtf(activeCounter), 
                    dc.interpolationMiliseconds));
                });
        });
    }
}

void 
DynamicAudioSystem::toggleTrack(HUGO::String trackName, Action action) {
    switch(action) {
        case ACTIVATE:
            activateTrack(trackName);
            break;
        case DEACTIVATE:
            deactivateTrack(trackName);
            break;
        case TOGGLE:
            if(trackEntities[trackName].active)
                deactivateTrack(trackName);
            else
                activateTrack(trackName);
            break;
    }
}

void
DynamicAudioSystem::onUpdateDyn(DynamicAudioComponent& dyn) {
    if(!scene.hasComponent<AudioComponent>(dyn.entity))
        return;

    if(trackEntities[dyn.audioName].active) {
        scene.modifyComponent<AudioComponent>(dyn.entity, [this, &dyn](AudioComponent& ac) {
           scene.modifyComponent<TweenComponent>(dyn.entity, [this, &ac, &dyn](TweenComponent& tc) {
               tc.currentTweens.clear();
               tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                   ac, 
                   &AudioComponent::volume, 
                   ac.volume, 
                   dyn.maxVolume / std::sqrtf(activeCounter), 
                   dyn.interpolationMiliseconds));
            });
        });
    }

    else {
        scene.modifyComponent<AudioComponent>(dyn.entity, [this, &dyn](AudioComponent& ac) {
            scene.modifyComponent<TweenComponent>(dyn.entity, [this, &ac, &dyn](TweenComponent& tc) {
                tc.currentTweens.clear();
                tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                    ac,
                    &AudioComponent::volume,
                    ac.volume,
                    dyn.minVolume,
                    dyn.interpolationMiliseconds));
            });
        });
    }
}
