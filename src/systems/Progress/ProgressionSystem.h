#pragma once

#include "HUGO.h"

HSYSTEM(ProgressionSystem)

    // time for clock
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int miliseconds = 0;

    // wave times
    int minutesBetweenWaves = 10;
    int minutesToNextWave = 10;

    int waveMinutesDuration = 5;
    int currentWaveMinutesLeft = 0;

    bool waveActive = false;

    // enemy level times
    int wavesUntilEnemyLevelUp = 2;
    int wavesToEnemyLevelUp = 2;

    // boss times
    int minutesUntilBoss = 30;
    int minutesBetweenBosses = 30;

    void changeEnemyDensity(bool increase);

public:

    void onLoad() override;
    void init() override;

    void update(uint32_t dt) override;
    void fixedUpdate(uint32_t) override;
END_HSYSTEM()