#include "DynamicAudioSystem.h"

#include "AudioComponent.h"
#include "EcsTypes.h"
#include "HugoEasings.h"
#include "HugoInputCodes.h"
#include "HugoTween.h"
#include "HugoTypes.h"
#include "TweenComponent.h"
#include <cmath>

void DynamicAudioSystem::init() {
  for (int i = 0; i < SIZE_OF_ID; ++i)
    musicEntities[i] = {createTrackEntity((SongID)i), false};

  activateTrack(BASE);
}

void DynamicAudioSystem::update(uint32_t dt) {
  if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::H)) {
    if (musicEntities[BASE].second) {
      deactivateTrack(BASE);
    } else {
      activateTrack(BASE);
    }
  }

  if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::J)) {
    if (musicEntities[MELODY].second)
      deactivateTrack(MELODY);
    else
      activateTrack(MELODY);
  }

  if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::K)) {
    if (musicEntities[HI_HAT].second)
      deactivateTrack(HI_HAT);
    else
      activateTrack(HI_HAT);
  }

  if (scene.getInput()->wasKeyJustPressed(HUGO::KeyCode::L)) {
    if (musicEntities[DRUMS].second)
      deactivateTrack(DRUMS);
    else
      activateTrack(DRUMS);
  }
}

EntityID DynamicAudioSystem::createTrackEntity(SongID song) {
  EntityID track = scene.createEntity();

  scene.addComponent<AudioComponent>(track, [song](AudioComponent &ac) {
    ac.loop = true;
    ac.volume = 0;
    ac.isPlaying = true;
    ac.type = HUGO::AudioTypes::MUSIC;

    switch (song) {
    case BASE:
      ac.audioName = "base";
      break;
    case MELODY:
      ac.audioName = "main";
      break;
    case DRUMS:
      ac.audioName = "kick-snare";
      break;
    case HI_HAT:
      ac.audioName = "hi-hat";
      break;

    default:
      break;
    };
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
        scene.modifyComponent<TweenComponent>(entity, [this, &ac](TweenComponent& tc) {
            tc.currentTweens.clear();
            tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                        ac, 
                        &AudioComponent::volume, 
                        ac.volume, 
                        1.0f / std::sqrtf(activeCounter), 
                        1500.f));
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
    scene.modifyComponent<AudioComponent>(entity, [this, entity, active](AudioComponent &ac) {
        if (!active || activeCounter == 0)
            scene.modifyComponent<TweenComponent>(entity, [this, &ac](TweenComponent& tc) {
                tc.currentTweens.clear();
                tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                            ac, 
                            &AudioComponent::volume, 
                            ac.volume, 
                            .0f, 
                            1500.0f));
            });
        else
            scene.modifyComponent<TweenComponent>(entity, [this, &ac](TweenComponent& tc) {
                tc.currentTweens.clear();
                tc.currentTweens.push_back(HUGO::TweenFactory<LinearTween>::makeTween(
                            ac, 
                            &AudioComponent::volume, 
                            ac.volume, 
                            1.0f / std::sqrtf(activeCounter), 
                            1500.f));
            });
      });
  }
}
