#pragma once

#include <cstdint>
#include <unordered_map>

#include "DynamicAudioComponent.h"
#include "EcsTypes.h"
#include "HugoSystemMacros.h"
#include "HugoTypes.h"
#include "DynamicTrackMessage.h"

HSYSTEM(DynamicAudioSystem)
    struct TrackEntity {
        EntityID entity;
        bool active;
    };

    std::unordered_map<HUGO::String, TrackEntity> trackEntities;
    int activeCounter = 0;

    void activateTrack(HUGO::String track);
    void deactivateTrack(HUGO::String track);

    void equalizeTracks();
    void toggleTrack(HUGO::String track, Action action);

    void onUpdateDyn(DynamicAudioComponent& dyn);
public:
    void update(uint32_t) override {}
    void fixedUpdate(uint32_t) override {}

    void init() override;
    void onLoad() override;
END_HSYSTEM()
