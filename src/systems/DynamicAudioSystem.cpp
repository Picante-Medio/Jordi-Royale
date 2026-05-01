#include "DynamicAudioSystem.h"

#include "AudioComponent.h"
#include "EcsTypes.h"
#include "HugoEasings.h"
#include "HugoInputCodes.h"
#include "HugoTween.h"
#include "HugoTypes.h"
#include "TweenComponent.h"
#include "DynamicAudioComponent.h"
#include <cmath>

void DynamicAudioSystem::init() {
    musicNames = {
        "base",
        "main",
        "kick-snare",
        "hi-hat",
    };

    for (int i = 0; i < SIZE_OF_ID; ++i)
        musicEntities[i] = {createTrackEntity((SongID)i), false};

    activateTrack(BASE);
}

void DynamicAudioSystem::update(uint32_t dt) {
    if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::H))
        toggleTrack(BASE);

    if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::J))
        toggleTrack(MELODY);

    if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::K)) 
        toggleTrack(HI_HAT);

    if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::L))
        toggleTrack(DRUMS);
}

EntityID DynamicAudioSystem::createTrackEntity(SongID song) {
    EntityID track = scene.createEntity();

    scene.addComponent<DynamicAudioComponent>(track, [this, song](DynamicAudioComponent& dc){
        dc.audioName = musicNames[song];
    });

    const DynamicAudioComponent& dc = scene.getComponentConst<DynamicAudioComponent>(track);

    scene.addComponent<AudioComponent>(track, [this,song,&dc](AudioComponent &ac) {
        ac.loop = true;
        ac.volume = dc.minVolume;
        ac.isPlaying = true;
        ac.type = HUGO::AudioTypes::MUSIC;
        ac.audioName = dc.audioName;
    });

    scene.addComponent<TweenComponent>(track);

    return track;
}

void DynamicAudioSystem::activateTrack(SongID track) {
    if (musicEntities[track].second)
        return;

    musicEntities[track].second = true;
    activeCounter++;

    for (auto [entity, active] : musicEntities) {
        if (!active)
            continue;

        scene.modifyComponent<AudioComponent>(entity, [entity, this](AudioComponent &ac) {
            scene.modifyComponent<TweenComponent>(entity, [this, entity, &ac](TweenComponent& tc) {
                const DynamicAudioComponent& dc = scene.getComponentConst<DynamicAudioComponent>(entity);
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

void DynamicAudioSystem::deactivateTrack(SongID track) {
    if (!musicEntities[track].second)
        return;

    musicEntities[track].second = false;
    activeCounter--;

    for (auto [entity, active] : musicEntities) {
        const DynamicAudioComponent& dc = scene.getComponentConst<DynamicAudioComponent>(entity);
        scene.modifyComponent<AudioComponent>(entity, [this, entity, active, &dc](AudioComponent &ac) {
            if (!active || activeCounter == 0)
                scene.modifyComponent<TweenComponent>(entity, [this, entity, &ac, &dc](TweenComponent& tc) {
                    tc.currentTweens.clear();
                    tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                        ac,
                        &AudioComponent::volume,
                        ac.volume,
                        dc.minVolume,
                        dc.interpolationMiliseconds));
            });
            else
                scene.modifyComponent<TweenComponent>(entity, [this, &ac, &dc](TweenComponent& tc) {
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
DynamicAudioSystem::toggleTrack(SongID track) {
    if(musicEntities[track].second)
        deactivateTrack(track);
    else
        activateTrack(track);
}
