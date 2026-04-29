#pragma once

#include "EcsTypes.h"
#include "HugoSystemMacros.h"
#include <array>
#include <cstdint>

HSYSTEM(DynamicAudioSystem)
    enum SongID {
        BASE,
        MELODY,
        DRUMS,
        HI_HAT,
        SIZE_OF_ID,
    };

    std::array<std::pair<EntityID, bool>, SIZE_OF_ID> musicEntities;
    int activeCounter = 0;

    EntityID createTrackEntity(SongID song);
    void activateTrack(SongID track);
    void deactivateTrack(SongID track);
public:
    void init() override;
    void update(uint32_t dt) override;

    void onLoad() override {};
    void fixedUpdate(uint32_t) override {}
END_HSYSTEM()
