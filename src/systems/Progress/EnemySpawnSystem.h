#pragma once
#include "HugoSystemMacros.h"
#include "HugoTypes.h"

#include <vector>

HSYSTEM(EnemySpawnSystem)
private:
    EntityID playerID;
    std::vector<HUGO::String> prefabs;
    std::vector<HUGO::String> bossPrefabs;

    HUGO::Int spawnTime = 2000;    //in miliseconds
    HUGO::Int enemySpawnTimer = 0;
    HUGO::Int enemyLevel = 1;

    const HUGO::Float spawnRadius = 20.f;

    void spawnEnemy(HUGO::String prefab);
public:
    void init() override;
    void update(uint32_t dt) override;

    void onLoad() override; 
    void fixedUpdate(uint32_t) override {};

END_HSYSTEM()
