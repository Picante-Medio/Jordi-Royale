#pragma once
#include "HugoSystemMacros.h"
#include "HugoTypes.h"
#include "JordiRandom.h"
#include <vector>

HSYSTEM(EnemySpawnSystem)
private:
EntityID playerID;
std::vector<HUGO::String> prefabs;
std::vector<HUGO::String> bossPrefabs;
std::vector<EntityID> spawners;
JordiRandom rnd;
HUGO::Int spawnTime = 1000;    //in miliseconds
HUGO::Int ms = 0;
HUGO::Int enemiesLevel = 1;
HUGO::Float timeVariance = 0.1;
HUGO::Float spawnVariance = 3.0;
HUGO::Int spawnTimeWithVariance;
HUGO::Int actWave;

void spawnEnemy(HUGO::String prefab);

public:
void init() override;
void onLoad() override;

void fixedUpdate(uint32_t) override;
void update(uint32_t) override;

END_HSYSTEM()