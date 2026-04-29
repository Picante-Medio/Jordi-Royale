#include "DynamicAudioSystem.h"

#include "EcsTypes.h"
#include "HugoInputCodes.h"
#include "AudioComponent.h"
#include "HugoTypes.h"

void 
DynamicAudioSystem::init() {
    for(int i = 0; i < SIZE_OF_ID; ++i) 
        musicEntities[i] = {createTrackEntity((SongID)i), false};

    musicEntities[BASE].second = true;
    activeCounter = 1;

    activateTrack(BASE);
}

void 
DynamicAudioSystem::update(uint32_t dt) {
    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::H)) {
        if(musicEntities[BASE].second)
            deactivateTrack(BASE);
        else
            activateTrack(BASE);
    }

    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::J)) {
        if(musicEntities[MELODY].second)
            deactivateTrack(MELODY);
        else
            activateTrack(MELODY);
    }

    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::K)) {
        if(musicEntities[HI_HAT].second)
            deactivateTrack(HI_HAT);
        else
            activateTrack(HI_HAT);
    }

    if(scene.getInput()->isKeyPressed(HUGO::KeyCode::L)) {
        if(musicEntities[DRUMS].second)
            deactivateTrack(DRUMS);
        else
            activateTrack(DRUMS);
    }
}


    
EntityID 
DynamicAudioSystem::createTrackEntity(SongID song) {
    EntityID track = scene.createEntity();

    scene.addComponent<AudioComponent>(track, [song](AudioComponent& ac){
        ac.loop = true;
        ac.volume = 0;
        ac.isPlaying = true;
        ac.type = HUGO::AudioTypes::MUSIC;

        switch(song) {
            case BASE:
                ac.audioName = "Base";
                break;
            case MELODY:
                ac.audioName = "Main";
                break;
            case DRUMS:
                ac.audioName = "Kick-Snare";
                break;
            case HI_HAT:
                ac.audioName = "Hi-hat";
                break;

            default:
                break;
        };

    });

    return track;
}

void
DynamicAudioSystem::activateTrack(SongID track) {
    if(musicEntities[track].second) 
        return;

    musicEntities[track].second = true;
    activeCounter++;

    for(auto [entity, active] : musicEntities) {
        if(!active) continue;

        scene.modifyComponent<AudioComponent>(entity, [this](AudioComponent& ac) {
            ac.volume = 1.0f / activeCounter;
        });
    }
}

void
DynamicAudioSystem::deactivateTrack(SongID track) {
    if(!musicEntities[track].second) 
        return;

    musicEntities[track].second = false;
    activeCounter--;

    for(auto [entity, active] : musicEntities) {
        scene.modifyComponent<AudioComponent>(entity, [this, active](AudioComponent& ac) {
            if(!active || activeCounter == 0) ac.volume = .0f;
            else ac.volume = 1.0f / activeCounter;
        });
    }
}
