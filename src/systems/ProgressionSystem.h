#pragma once

#include "HugoSystemMacros.h"

HSYSTEM(ProgressionSystem)

    // time for clock
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int miliseconds = 0;

    int minutesBetweenWaves = 10;
    int minutesToNextWave = 10;

    int waveMinutesDuration = 5;
    int currentWaveMinutesLeft = 0;

    bool waveActive = false;

    int wavesUntilEnemyLevelUp = 2;
    int wavesToEnemyLevelUp = 2;

    void changeEnemyDensity(bool increase);

public:

    void onLoad() override;
    void init() override;

    void update(uint32_t dt) override;
    void fixedUpdate(uint32_t) override;
END_HSYSTEM()